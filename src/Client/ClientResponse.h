#ifndef CLIENTRESPONSE_H
#define CLIENTRESPONSE_H

// #include <memory>
// #include <unistd.h>
#include <iostream>
#include "../Message/Message.h"

class ClientResponse {

    int number_of_tasks;

    Message resp;
    Message::STATUS status;
    int task;

    void Command(Message* rcvd);
    void Response(Message* rcvd);

public:
    ClientResponse(int _serial_number, int _number_of_tasks, int first_task = 0);
    virtual ~ClientResponse();
    void Processing(Message* rcvd);
    Message::STATUS GetStatus() { return status;    }
    int GetTask()               { return task;      }
    Message GetResponce()       { return resp;      }

};

#endif // CLIENTRESPONSE_H
