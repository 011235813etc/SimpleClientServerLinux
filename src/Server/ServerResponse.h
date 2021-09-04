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
    void CommandClientReady(Message* from_client);

    void ResponseClientDone(Message* from_client);
    void ResponseClientReady(Message* from_client);
public:
    explicit ServerResponse(int serial_number);
    ServerResponse(const ServerResponse& other);
    ServerResponse& operator=(const ServerResponse& other);
    ServerResponse& operator=(const ServerResponse&& other);
    virtual ~ServerResponse();
    void Processing(Message* from_client);
    void SaveCommand(int task);
    bool IsNeedResponse();

#ifdef DEBUG
    //! \brief Set accepting commands status (use only unit tests).
    //! \param bool complete - commands load status.
	//! \return void.
    void SetAcceptingCommands(bool accepting) {
        isAcceptingCommands = accepting;
    }

    //! \brief Get saved commands count.
	//! \return int - commands count.
    int GetSavedCommandsCount() {
        return task_queue.size();
    }

    //! \brief Getting status accepting commands
    //! \return bool - status accepting commands.
    bool IsAcceptingCommands() {
        return isAcceptingCommands;
    }
#endif //DEBUG
};

#endif // SERVERRESPONSE_H
