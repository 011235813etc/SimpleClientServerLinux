//! \file BaseResponse.cpp
//! \brief BaseResponse class declaration.

#ifndef BASERESPONSE_H
#define BASERESPONSE_H

#include <iostream>
#include "../Message/Message.h"

//! \brief This class used as base class for prepare response for client/server. 
class BaseResponse {
protected:
    int total_tasks;        //!< Used for save total number of  tasks.
    Message response;       //!< Used for save response or command.
    STATUS status;          //!< Used for save currant status.
    int task;               //!< Used for save current task.
    bool isNeedResponse;    //!< Used for forming response.

    //! \brief Preparing command message to server.
    //! \param Message* received - Pointer to received message from server.
    //! \return void.
    virtual void Command(Message* received) = 0;

    //! \brief Preparing response message to server.
    //! \param Message* received - Pointer to received message from server.
    //! \return void.
    virtual void Response(Message* received) = 0;

public:
    BaseResponse(int serial_number, int total_tasks, int first_task = Message::launch_task);
    BaseResponse(const BaseResponse& other);
    BaseResponse& operator=(const BaseResponse& other);
    BaseResponse& operator=(const BaseResponse&& other);
    //! \brief Class destructor.
    virtual ~BaseResponse() {};

    //! \brief Processing message.
    //! \param Message* received - Pointer to received message from server.
    //! \return void.
    virtual void Processing(Message* received) = 0;

    STATUS GetStatus();
    int GetTask();
    Message GetResponce();
    void SetStatus(STATUS status);

    bool IsNeedResponse();
};

#endif // BASERESPONSE_H
