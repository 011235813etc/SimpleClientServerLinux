#include "Server.h"

Server::Server(uint32_t timeout_sec) {

	task = 0;

	timeout.tv_sec = timeout_sec;
	timeout.tv_usec = 0;

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if(listener < 0) 
	{
		perror("socket");
		exit(1);
	}

	fcntl(listener, F_SETFL, O_NONBLOCK);
	
	
	soc_addr = std::unique_ptr<SocketAddress>(new SocketAddress("127.0.0.1", 3425));
	
	if(bind(listener, (struct sockaddr*)soc_addr->GetPtr(), soc_addr->GetSize()) < 0)
	{
		perror("bind");
		exit(2);
	}

	listen(listener, 2);
}

Server::~Server() {
    close(listener);
}


void Server::CreateSocketQueue(std::set<int>& clients, fd_set& readset) {
	using namespace std;
	
	FD_ZERO(&readset);
	FD_SET(listener, &readset);

	for(set<int>::iterator it = clients.begin(); it != clients.end(); it++) {
		FD_SET(*it, &readset);
	}
}


void Server::WaitEvent(std::set<int>& clients, fd_set& readset) {
	using namespace std;
	
	//Ждем события в одном из сокетов
	int mx = max(listener, *max_element(clients.begin(), clients.end()));
	if(select(mx+1, &readset, NULL, NULL, &timeout) <= 0) {
		perror("select");
		exit(3);
	}
}

void Server::AddNewClientsRequests(std::set<int>& clients, fd_set& readset) {
	//определяем тип события и выполняем соответствующие действия
	if(FD_ISSET(listener, &readset)) {
		//поступил новый запрос на соединение, используем accept
		int sock = accept(listener, NULL, NULL);
		if(sock < 0) {
			perror("accept");
			exit(3);
		}
		fcntl(sock, F_SETFL, O_NONBLOCK);
		clients.insert(sock);
	}
}

void Server::DataProcessing(Message* response, int bytes_read) {

	std::cout << "<< Received message from client:" << std::endl;
	std::cout << response[0] << std::endl;
	
	switch(response->action) {
	    case Message::ACTION::COMMAND: {
	    	CommandProcessing(response);
	    	break;
	    }
        case Message::ACTION::RESPONSE: {
        	ResponseProcessing(response);
        	break;
        }
        default: std::cout << "UNKNOWN ACTION TYPE" << std::endl; break;
	}
	
	//! FIXME it shouldn't be here
	std::cout << ">> Send message to client:" << std::endl;
	std::cout << response[0] << std::endl << std::endl;
}

void Server::CommandProcessing(Message* response) {
	
    switch(response->status) {
        case Message::STATUS::BUSY: {
			response->Response(Message::STATUS::ACCEPTED, serial_number);
			break;
        }
        case Message::STATUS::ERROR: std::cout << "ERROR!" << std::endl; 		break;
        //TODO просмотреть в стеке задач наличие задачи с таким номером
        case Message::STATUS::DONE: std::cout << "DONE" << std::endl; 		break;
        
        case Message::STATUS::READY: {
			response->Response(Message::STATUS::ACCEPTED, serial_number);
        	task 	= response->task;
			break;
		}	
        case Message::STATUS::ACCEPTED:	 std::cout << "ACCEPTED" << std::endl; 	break;
        default: std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				break;
    }
}


void Server::ResponseProcessing(Message* response) {
	
    switch(response->status) {
        case Message::STATUS::BUSY: {
			response->Response(Message::STATUS::ACCEPTED, serial_number);
			break;
        }
        case Message::STATUS::ERROR: std::cout << "ERROR!" << std::endl; 		break;
        case Message::STATUS::DONE:
        case Message::STATUS::READY: {
        	std::cout << ">> Set task #" << task << std::endl;
        	response->task = task;
			response->Response(Message::STATUS::ACCEPTED, serial_number);
			break;
		}	
        case Message::STATUS::ACCEPTED:	 std::cout << "ACCEPTED" << std::endl; 	break;
        default: std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				break;
    }
}


