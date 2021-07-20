#include "Client.h"

Client::Client(Message::CLIENT_TYPE type) {

//    msg.client = type;

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
//    send(sock_descriptor, reinterpret_cast<void*>(&msg), sizeof(msg), 0);
    send(sock_descriptor, msg, sizeof(msg), 0);
}
void Client::Recv() {
//    recv(sock_descriptor, reinterpret_cast<void*>(&msg), sizeof(msg), 0);
    recv(sock_descriptor, buf, sizeof(buf), 0);
}

void Client::PrintBuf() {

//    message* msg = reinterpret_cast<message*>(&buf);


}

