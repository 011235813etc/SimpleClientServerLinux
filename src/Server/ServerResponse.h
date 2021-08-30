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

    std::queue<int> task_queue;         //!< Using for save commands from Client.
    bool isAllCommandsReceived = false; //!< Using as a sign all command receive.

    void Command(Message* from_client);
    void Response(Message* from_client);
public:
    ServerResponse(int serial_number);
    virtual ~ServerResponse();
    void Processing(Message* from_client);
    void SaveCommand(int task);
    void SetCommandsLoadComplete(bool complete);
};

#endif // SERVERRESPONSE_H
