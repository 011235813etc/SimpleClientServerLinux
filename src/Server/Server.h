#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <unistd.h>
#include <iostream>
#include "../SocketAddress/SocketAddress.h"
#include "../Message/Message.h"
#include <fcntl.h>
#include <algorithm>
#include <set>

class Server {
    std::unique_ptr<SocketAddress> soc_addr;
    int listener;

public:
    explicit Server();
    virtual ~Server();
    int GetListener();
};

#endif // SERVER_H
