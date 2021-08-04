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
    std::unique_ptr<SocketAddress> soc_addr;
    Message msg;
    int sock_descriptor;
    char buf[sizeof(msg)];
    static int serial_number;
    
    Message::STATUS status;
    int task;

    int number_of_tasks;

    std::unique_ptr<ClientResponse> reply;
    
    // void CommandProcessing(Message* response);
    // void ResponseProcessing(Message* response);
    // bool IsTaskListEmpty();

public:
    explicit Client(Message::ACTION action=Message::ACTION::COMMAND);
    virtual ~Client();
    void Send();
    void Recv();
    // void PrintBuf();
    void Send(Message& _msg);
    int GetSerialNumber() { return serial_number; }

    friend std::ostream& operator <<(std::ostream& os, const Message);
};

#endif // CLIENT_H
