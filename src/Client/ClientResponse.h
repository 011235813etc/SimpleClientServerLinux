/*! \file ClientResponse.h
    \brief ClientResponse class declaration. 
*/
#ifndef CLIENTRESPONSE_H
#define CLIENTRESPONSE_H

#include <iostream>
#include <chrono>
#include <thread>
#include "../Message/Message.h"
#include "../BaseResponse/BaseResponse.h"

class ClientResponse : public BaseResponse {
    void Command(Message* from_server);
    void Response(Message* from_server);
    bool loadingTasks;                  //!< Used as a sing for load tasks to server.

    void CommandServerReady(Message* from_server);

    void ResponseServerBusy(Message* from_server);
    void ResponseServerReady(Message* from_server);
    void ResponseServerAccepted(Message* from_server);
    void ResponseServerDone(Message* from_server);
public:
    ClientResponse(int serial_number, int total_tasks, int first_task = Message::launch_task);
    //! \brief Class destructor.
    virtual ~ClientResponse() = default;
    void Processing(Message* from_server);
    bool IsLoading();
    void RequestCommandFromServer();
    bool IsTasksDone();
    

#ifdef DEBUG
    //! \brief Set loading sign is true (Used for unit testing).
    void SetLoading() {
        loadingTasks = true;
    }
#endif //DEBUG
};

#endif // CLIENTRESPONSE_H
