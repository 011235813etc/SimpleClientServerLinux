/*! \file ServerResponse.h
    \brief ServerResponse class declaration.
*/

#ifndef SERVERRESPONSE_H
#define SERVERRESPONSE_H

#include <iostream>
#include <queue>
#include "../Message/Message.h"
#include "../BaseResponse/BaseResponse.h"

class ServerResponse : public BaseResponse {

    std::queue<int> task_queue;     //!< Using for save commands from Client.

    void Command(Message* rcvd);
    void Response(Message* rcvd);
public:
    ServerResponse(int serial_number);
    virtual ~ServerResponse();
    void Processing(Message* rcvd);
    void SaveCommand(int task);
};

#endif // SERVERRESPONSE_H
