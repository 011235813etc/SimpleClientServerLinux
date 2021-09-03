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

    std::queue<int> task_queue;         //!< Used for save commands from Client.
    bool isAcceptingCommands;           //!< Used as a sign accepting commands.
    bool isNeedResponse;                //!< Used for forming response.

    void Command(Message* from_client);
    void Response(Message* from_client);

    void CommandClientDone(Message* from_client);
    void CommandClientError(Message* from_client);
    void CommandClientBusy(Message* from_client);
    void CommandClientAccepted(Message* from_client);
    void CommandClientReady(Message* from_client);

    void ResponseClientDone(Message* from_client);
    void ResponseClientError(Message* from_client);
    void ResponseClientBusy(Message* from_client);
    void ResponseClientAccepted(Message* from_client);
    void ResponseClientReady(Message* from_client);
public:
    ServerResponse(int serial_number);
    virtual ~ServerResponse();
    void Processing(Message* from_client);
    void SaveCommand(int task);
    void SetAcceptingCommands(bool accepting);
    bool IsNeedResponse();
};

#endif // SERVERRESPONSE_H
