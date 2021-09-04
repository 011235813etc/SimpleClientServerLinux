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
    ClientResponse(const ClientResponse& other);
    ClientResponse& operator=(const ClientResponse& other);
    ClientResponse& operator=(const ClientResponse&& other);
    //! \brief Class destructor.
    virtual ~ClientResponse() = default;
    void Processing(Message* from_server);
    bool IsLoading();
    void RequestCommandFromServer();
    bool IsTasksDone();
    

#ifdef DEBUG
    //! \brief Set loading sign is true (Used for unit testing).
    //! \param bool new_status - new loading status.
    //! \return void.
    void SetLoading(bool new_status) {
        loadingTasks = new_status;
    }
    //! \brief Get loading status (Used for unit testing).
    //! \return bool - loading status.
    bool GetLoading() {
        return loadingTasks;
    }

    //! \brief Set new task (Used for unit testing).
    //! \param int task - new task.
    //! \return void.
    void SetTask(int task) {
        this->task = task;
    }
#endif //DEBUG
};

#endif // CLIENTRESPONSE_H
