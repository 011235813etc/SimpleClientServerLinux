/*! \file Client.h
    \brief Client class declaration.
*/
#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <unistd.h>
#include <iostream>
#include "../SocketAddress/SocketAddress.h"
#include "../Message/Message.h"
#include <time.h>
#include "ClientResponse.h"

class Client {
    std::unique_ptr<SocketAddress> soc_addr;    //!< Current socket address.
    Message msg;                                //!< Using for save prepare message.
    int sock_descriptor;                        //!< Using for save socket.
    char buf[sizeof(msg)];                      //!< Buffer for save received information.
    static int serial_number;                   //!< Client serial number.
    int total_tasks_numer;                      //!< Using for set commads for Server.
    std::unique_ptr<ClientResponse> to_server;  //!< Using for prepare response message for Server.
public:
    explicit Client(Message::ACTION action=Message::ACTION::COMMAND);
    virtual ~Client();
    void Send();
    void Recv();
    void Send(Message& _msg);
    int GetSerialNumber();
};

#endif // CLIENT_H
