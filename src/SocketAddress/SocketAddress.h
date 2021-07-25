#ifndef SOCKETADDRESS_H
#define SOCKETADDRESS_H

#include <arpa/inet.h>

class SocketAddress {
    struct sockaddr_in sock_addr;
    public:
        SocketAddress(const char* addr, uint32_t port) {
            sock_addr.sin_family = AF_INET;
            sock_addr.sin_port = htons(port);
            inet_pton(AF_INET, addr, &sock_addr.sin_addr);
        }
        virtual ~SocketAddress() { };

        size_t GetSize() const { return sizeof(sock_addr); }
        sockaddr_in* GetPtr() { return &sock_addr; }

};

#endif // SOCKETADDRESS_H
