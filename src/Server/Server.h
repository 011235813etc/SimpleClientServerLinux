#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <unistd.h>
#include <iostream>
#include "../SocketAddress/SocketAddress.h"
#include "../Message/Message.h"

class Server {
    std::unique_ptr<SocketAddress> soc_addr;
    int sock_descriptor;
//    message msg;
    char buf[1024];

public:
    explicit Server();
    virtual ~Server();
};

#endif // SERVER_H
