#ifndef BASERESPONSE_H
#define BASERESPONSE_H

#include <iostream>
#include "../Message/Message.h"

class BaseResponse {
protected:
    int total_tasks;

    Message resp;
    Message::STATUS status;
    int task;

    virtual void Command(Message* rcvd) = 0;
    virtual void Response(Message* rcvd) = 0;

public:
    BaseResponse(int serial_number, int total_tasks, int first_task = 0);
    virtual ~BaseResponse() {};
    void Processing(Message* rcvd);

    Message::STATUS GetStatus()             { return status;    }
    int GetTask()                           { return task;      }
    Message GetResponce()                   { return resp;      }
    void SetStatus(Message::STATUS status)  { this->status = status;    }
};

#endif // BASERESPONSE_H
