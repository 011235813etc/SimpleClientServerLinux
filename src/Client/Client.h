#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <unistd.h>
#include <iostream>
#include "../SocketAddress/SocketAddress.h"
#include "../Message/Message.h"

class Client {
    std::unique_ptr<SocketAddress> soc_addr;
    Message msg;
    int sock_descriptor;
//    const char msg[7] = "Hello\n";
    char buf[sizeof(msg)];

public:
    explicit Client(Message::CLIENT_TYPE type=Message::CLIENT_TYPE::COMMON);
    virtual ~Client();
    void Send();
    void Recv();
    void PrintBuf();

    friend std::ostream& operator <<(std::ostream& os, const Message);
};

#endif // CLIENT_H
