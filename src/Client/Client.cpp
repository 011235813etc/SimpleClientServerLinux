#include "Client.h"

int Client::serial_number = 0;

Client::Client(Message::ACTION action) {

	//! initialize random seed
	srand(time(NULL));
	
	//! generate serial number between 1 and 100 
	serial_number = rand() % 100 + 1;

    msg = Message();
    msg.action = action;
    msg.source = serial_number;

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
}

void Client::PrintBuf() {

//    message* msg = reinterpret_cast<message*>(&buf);
//    std::cout << buf << std::endl;

	std::cout << "<< Received message from server:" << std::endl;
	auto echo_msg = reinterpret_cast<Message*>(buf);
	std::cout << *echo_msg << std::endl;

}

void Client::Send(Message& _msg) {
    send(sock_descriptor, reinterpret_cast<void*>(&_msg), sizeof(_msg), 0);
//    send(sock_descriptor, msg, sizeof(msg), 0);

	std::cout << ">> Send message to server:" << std::endl;
	std::cout << _msg << std::endl << std::endl;
}


