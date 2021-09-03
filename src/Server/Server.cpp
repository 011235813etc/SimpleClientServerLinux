/*! \file Server.cpp
    \brief Server class implementation.

    This class describe Server.
    Class include description socket connection with Client.
*/

#include "Server.h"

/*! 
    \brief Constructor with argument.
    \param uint32_t timeout_sec - timeout for waiting response from Client.
*/ 
Server::Server(uint32_t timeout_sec) {
	
	task = 0;

	// Using only with seconds value,
	// because in this case milliseconds not important for me.
	timeout.tv_sec = timeout_sec; 
	timeout.tv_usec = 0;

	// Create lisener socket descriptor.
	listener = socket(AF_INET, SOCK_STREAM, 0);
	if(listener < 0) 
	{
		perror("socket");
		exit(1);
	}

	// Create nonblocking sockets.
	fcntl(listener, F_SETFL, O_NONBLOCK);
	
	// Create socket address.
	soc_addr = std::unique_ptr<SocketAddress>(new SocketAddress("127.0.0.1", 3425));
	
	// Link to a socket.
	if(bind(listener, (struct sockaddr*)soc_addr->GetPtr(), soc_addr->GetSize()) < 0)
	{
		perror("bind");
		exit(2);
	}
	// Waiting for requests.
	listen(listener, 2);

	// Create ServerResponse class object for save response message for Client.
	prepare_response = std::unique_ptr<ServerResponse>(new ServerResponse(serial_number));
	status = Message::STATUS::READY;
	to_client = Message(Message::ACTION::RESPONSE, Message::STATUS::READY, Message::launch_task, serial_number); 
}

/*! 
    \brief Class destructor.

	Close socket.
*/ 
Server::~Server() {
    close(listener);
}

/*! 
    \brief Processing Client response.
    \param std::set<int>& clients - set with clients.
    \param fd_set& readset - socket descriptor.
	\return void.
*/
void Server::CreateSocketQueue(std::set<int>& clients, fd_set& readset) {
	using namespace std;
	
	FD_ZERO(&readset);
	FD_SET(listener, &readset);

	for(set<int>::iterator it = clients.begin(); it != clients.end(); it++) {
		FD_SET(*it, &readset);
	}
}

/*! 
    \brief Processing Client response.
    \param std::set<int>& clients - set with clients.
    \param fd_set& readset - socket descriptor.
	\return void.
*/
void Server::WaitEvent(std::set<int>& clients, fd_set& readset) {
	using namespace std;
	
	//! Waiting events on one of sockets
	int mx = max(listener, *max_element(clients.begin(), clients.end()));
	if(select(mx+1, &readset, NULL, NULL, &timeout) <= 0) {
		perror("select");
		exit(3);
	}
}

/*! 
    \brief Processing Client response.
    \param[in] std::set<int>& clients - clients set.
    \param[in] fd_set& readset - socket descriptor.
	\return void.
*/
void Server::AddNewClientsRequests(std::set<int>& clients, fd_set& readset) {
	// Determine the type of event
	if(FD_ISSET(listener, &readset)) {
		// Processing connection request
		int sock = accept(listener, NULL, NULL);
		if(sock < 0) {
			perror("accept");
			exit(3);
		}
		fcntl(sock, F_SETFL, O_NONBLOCK);
		clients.insert(sock);
	}
}

/*! 
    \brief Processing Client response.
    \param[in, out] Message* from_client - pointer to the buffer.
	\return void.
*/
void Server::DataProcessing(Message* from_client, int sock_descriptor) {

    std::cout << ">> Received message from client:" << std::endl;
	std::cout << from_client[0] << std::endl;

	prepare_response->Processing(from_client);
	if(prepare_response->IsNeedResponse()) {
		to_client = prepare_response->GetResponce();
		send(sock_descriptor, reinterpret_cast<void*>(&to_client), sizeof(to_client), 0);
		std::cout << "<< Send message to client:" << std::endl;
		std::cout << to_client << std::endl << std::endl;
	}


}

/*! 
    \brief Set new task
    \param uint8_t task - new task.
    \param void.
*/ 
void Server::SetTask(uint8_t task) { 
	this->task = task;	
}

/*! 
    \brief Get current task.
    \return int task - current task.
*/ 
int Server::GetTask() { 
	return task;	
}