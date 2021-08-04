#ifndef CLIENTRESPONSE_H
#define CLIENTRESPONSE_H

// #include <memory>
// #include <unistd.h>
#include <iostream>
#include "../Message/Message.h"

class ClientResponse {

    int number_of_tasks;

    Message resp;
    Message::STATUS current_status;
    int current_task;

    void Command(Message* rcvd, int task, Message::STATUS status);
    void Response(Message* rcvd, int task, Message::STATUS status);

public:
    ClientResponse(int _serial_number, int _number_of_tasks);
    virtual ~ClientResponse();
    void Processing(Message* rcvd, int task, Message::STATUS status);
    Message::STATUS GetStatus() { return current_status; }
    int GetTask() { return current_task; }
    Message GetResponce() { return resp; }

};

#endif // CLIENTRESPONSE_H
