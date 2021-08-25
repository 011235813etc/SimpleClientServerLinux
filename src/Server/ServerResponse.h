#ifndef SERVERRESPONSE_H
#define SERVERRESPONSE_H

#include <iostream>
#include <queue>
#include "../Message/Message.h"
#include "../BaseResponse/BaseResponse.h"

class ServerResponse : public BaseResponse {

    std::queue<int> task_queue;

    void Command(Message* rcvd);
    void Response(Message* rcvd);

public:
    ServerResponse(int serial_number);
    virtual ~ServerResponse();
    void Processing(Message* rcvd);


    void SaveCommand(int task) {
        task_queue.push(task);
    }
};

#endif // SERVERRESPONSE_H
