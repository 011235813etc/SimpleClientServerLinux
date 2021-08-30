/*! \file Client.cpp
    \brief Client class implementation.

    This class using for exchange information with Server. 
    Class include description socket connection with Server.
*/

#include "Client.h"

int Client::serial_number = 0;

/*! 
    \brief Constructor with argument.
    \param const ACTION _action - type of action for client or server.
*/
Client::Client(Message::ACTION action) {

	srand(time(NULL));
	serial_number = rand() % 100 + 1; 
    total_tasks_numer = 5;

    msg = Message(action, Message::STATUS::READY, Message::launch_task, serial_number); 

    soc_addr = std::unique_ptr<SocketAddress>(new SocketAddress("127.0.0.1", 3425));

    sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_descriptor < 0) {
        perror("socket");
        exit(1);
    }

    if(connect(sock_descriptor, (struct sockaddr*)soc_addr->GetPtr(), soc_addr->GetSize()) < 0) {
        perror("connect");
        exit(2);
    }
    to_server = std::unique_ptr<ClientResponse>(new ClientResponse(serial_number, total_tasks_numer));
}

/*! 
    \brief Class destructor.

    Close socket.
 */ 
Client::~Client() {
    close(sock_descriptor);
}

/*! 
    \brief Send message to Server.
    \return void
 */ 
void Client::Send() {
    send(sock_descriptor, reinterpret_cast<void*>(&msg), sizeof(msg), 0);

	std::cout << ">> Send message to server:" << std::endl;
	std::cout << msg << std::endl << std::endl;
}

/*! 
    \brief Receive message from Server.
    \return void
 */ 
void Client::Recv() {
    recv(sock_descriptor, buf, sizeof(buf), 0);
    
	auto from_server = reinterpret_cast<Message*>(buf);
    std::cout << "<< Received message from server:" << std::endl;
	std::cout << from_server[0] << std::endl;

    to_server->Processing(from_server);
}

/*! 
    \brief Send message to Server.
    \param[in] Message& _msg - from_server message for Server.
    \return void
*/ 
void Client::Send(Message& _msg) {
    send(sock_descriptor, reinterpret_cast<void*>(&_msg), sizeof(_msg), 0);
//    send(sock_descriptor, msg, sizeof(msg), 0);

	std::cout << ">> Send message to server:" << std::endl;
	std::cout << _msg << std::endl << std::endl;
}

/*! 
    \brief Get Client serial number.
    \return int - serial number.
*/ 
int Client::GetSerialNumber()  {
    return serial_number;
}