#include "Client.h"

int Client::serial_number = 0;

Client::Client(Message::ACTION action) {

	//! initialize random seed
	srand(time(NULL));
	
	//! generate serial number between 1 and 100 
	serial_number = rand() % 100 + 1;
	
	status = Message::STATUS::READY;
	task = 0;
    number_of_tasks = 5;

    msg = Message();
    msg.action = action;
    msg.sender = serial_number;

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
}

Client::~Client() {
    close(sock_descriptor);
}

void Client::Send() {
    send(sock_descriptor, reinterpret_cast<void*>(&msg), sizeof(msg), 0);
//    send(sock_descriptor, msg, sizeof(msg), 0);

	std::cout << ">> Send message to server:" << std::endl;
	std::cout << msg << std::endl << std::endl;
}
void Client::Recv() {
//    recv(sock_descriptor, reinterpret_cast<void*>(&msg), sizeof(msg), 0);
    recv(sock_descriptor, buf, sizeof(buf), 0);
    
	auto response = reinterpret_cast<Message*>(buf);
    std::cout << "<< Received message from server:" << std::endl;
	std::cout << response[0] << std::endl;
	
	switch(response->action) {
	    case Message::ACTION::COMMAND: {
	    	CommandProcessing(response);
	    	break;
	    }
        case Message::ACTION::RESPONSE: {
//        	response->task = task;
//        	std::cout << ">> Set task #" << task << std::endl;
        	break;
        }
        default: std::cout << "UNKNOWN ACTION TYPE" << std::endl; break;
	}
}

void Client::PrintBuf() {

//    message* msg = reinterpret_cast<message*>(&buf);
//    std::cout << buf << std::endl;

//	std::cout << "<< Received message from server:" << std::endl;
//	auto echo_msg = reinterpret_cast<Message*>(buf);
//	std::cout << *echo_msg << std::endl;

}

void Client::Send(Message& _msg) {
    send(sock_descriptor, reinterpret_cast<void*>(&_msg), sizeof(_msg), 0);
//    send(sock_descriptor, msg, sizeof(msg), 0);

	std::cout << ">> Send message to server:" << std::endl;
	std::cout << _msg << std::endl << std::endl;
}

void Client::CommandProcessing(Message* response) {
    
    switch(status) {
        case Message::STATUS::BUSY: 
        case Message::STATUS::ERROR: {
			response->Response(status, serial_number);
			break;
        }
        case Message::STATUS::DONE:
        case Message::STATUS::READY: {
			response->Response(Message::STATUS::ACCEPTED, serial_number);
        	task 	= response->task;
			status 	= Message::STATUS::BUSY;
			break;
		}	
        case Message::STATUS::ACCEPTED: {	 
            std::cout << "ACCEPTED" << std::endl; 	
            break;
        }
        default: {
            std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				
            break;
        }
    }
}

void Client::ResponseProcessing(Message* response) {
    
    switch(status) {
        case Message::STATUS::BUSY: 
        case Message::STATUS::ERROR: {
			response->Response(Message::STATUS::ACCEPTED, serial_number);
			break;
        }
        case Message::STATUS::DONE:
        case Message::STATUS::READY: 
        case Message::STATUS::ACCEPTED: {

            if(IsTaskListEmpty()) {
			    response->Response(Message::STATUS::ACCEPTED, serial_number);
            } else {
                response->task = task;
            	std::cout << ">> Send to server task #" << task << std::endl;
                response->Command(Message::STATUS::READY, serial_number);
            }
			break;
		}	
        default: { 
            std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				
            break;
        }
    }
}

bool Client::IsTaskListEmpty() { 
    return task == number_of_tasks; 
}