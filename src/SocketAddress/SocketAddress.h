/*! \file SocketAddress.h
    \brief ServerResponse class implementation.

    Preparong socket address
*/
#ifndef SOCKETADDRESS_H
#define SOCKETADDRESS_H

#include <arpa/inet.h>

class SocketAddress {
    struct sockaddr_in sock_addr;   //!< Struct for save socket address.                    
public:
    /*! 
        \brief Constructor with argument.
        \param const char* addr - IP-address.
        \param uint32_t port - port number.
    */ 
    SocketAddress(const char* addr, uint32_t port) {
        sock_addr.sin_family = AF_INET;
        sock_addr.sin_port = htons(port);
        inet_pton(AF_INET, addr, &sock_addr.sin_addr);
    }
    //! \brief Class destructor.
    virtual ~SocketAddress() = default;

    /*! 
        \brief Processing Client response.
        \return size_t - size of socket struct.
    */
    size_t GetSize() const { return sizeof(sock_addr); }
    
    /*! 
        \brief Processing Client response.
        \return sockaddr_in* - pointer of socket struct.
    */
    sockaddr_in* GetPtr() { return &sock_addr; }

};

#endif // SOCKETADDRESS_H
