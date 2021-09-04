//! \file Client.cpp
//! \brief Client class implementation.
//! 
//! This class using for exchange information with Server. 
//! Class include description socket connection with Server.

#include "Client.h"

int Client::serial_number = 0;

//! \brief Constructor with argument.
//! \param const ACTION _action - type of action for client or server.
Client::Client(ACTION action, unsigned int total_tasks) {

	srand(time(NULL));
	serial_number = rand() % 100 + 1; 

    to_server = Message(action, STATUS::READY, Message::launch_task, serial_number); 

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
    prepare_response = std::unique_ptr<ClientResponse>(new ClientResponse(serial_number, total_tasks));
    from_server = reinterpret_cast<Message*>(buf);
}

//! \brief Class destructor.
//! Close socket.
Client::~Client() {
    close(sock_descriptor);
}

//! \brief Receive message from Server.
//! \return void
void Client::Recv() {
    recv(sock_descriptor, buf, sizeof(buf), 0);
    
	auto from_server = reinterpret_cast<Message*>(buf);
    std::cout << ">> Received message from server:" << std::endl;
	std::cout << from_server[0] << std::endl;

    // prepare_response->Processing(from_server);
#ifdef DEBUG
    if(enableHistoryRecording) {
        history.push_back(std::make_pair(from_server[0], TYPE::RECEIVED));
    }
#endif //DEBUG
}

//! \brief Send message to Server.
//! \param[in] Message& _to_server - from_server message for Server.
//! \return void.
void Client::Send(Message& _to_server) {
    send(sock_descriptor, reinterpret_cast<void*>(&_to_server), sizeof(_to_server), 0);
//    send(sock_descriptor, to_server, sizeof(to_server), 0);

	std::cout << "<< Send message to server:" << std::endl;
	std::cout << _to_server << std::endl << std::endl;

#ifdef DEBUG
    if(enableHistoryRecording) {
        history.push_back(std::make_pair(_to_server, TYPE::SENT));
    }
#endif //DEBUG
}

//! \brief Processing meaasge from server.
//! \param Message* from_server - Pointer to received message from Server.
//! \return void.
void Client::DataProcessing(Message* from_server) {
    prepare_response->Processing(from_server);
}

//! \brief Get Client serial number.
//! \return int - serial number.
int Client::GetSerialNumber()  {
    return serial_number;
}

//! \brief Launch to set commands to server.
//! \return void.
void Client::LoadTasks() {
    unsigned int task = 0;
    Send(to_server);
    Recv();
    DataProcessing(from_server);

    while(prepare_response->IsLoading()) {
        to_server = prepare_response->GetResponce();
        Send(to_server);
        Recv();
        DataProcessing(from_server);
    }
} 

//! \brief Request next command from server.
//! \return int - new command.
int Client::CommandRequest() {

    prepare_response->RequestCommandFromServer();
    to_server = prepare_response->GetResponce();
    
    Send(to_server);
    Recv();
    DataProcessing(from_server);

    if(!prepare_response->IsTasksDone()) {
        to_server = prepare_response->GetResponce();
        Send(to_server);
        return from_server[0].task;
    }
    return -1;

}