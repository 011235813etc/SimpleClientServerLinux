#ifndef SERVERRESPONSE_H
#define SERVERRESPONSE_H

// #include <memory>
// #include <unistd.h>
#include <iostream>
#include <stack>
#include "../Message/Message.h"

class ServerResponse {

    Message resp;
    Message::STATUS current_status;
    int current_task;

    std::stack<int> task_stack;

    void Command(Message* rcvd, Message::STATUS status);
    void Response(Message* rcvd, Message::STATUS status);

public:
    ServerResponse(int _serial_number);
    virtual ~ServerResponse();
    void Processing(Message* rcvd, Message::STATUS status);
    Message::STATUS GetStatus() { return current_status; }
    int GetTask() { return current_task; }
    Message GetResponce() { return resp; }
};

#endif // SERVERRESPONSE_H
