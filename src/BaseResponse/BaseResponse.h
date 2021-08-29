/*! \file BaseResponse.cpp
    \brief BaseResponse class declaration.
*/
#ifndef BASERESPONSE_H
#define BASERESPONSE_H

#include <iostream>
#include "../Message/Message.h"

class BaseResponse {
protected:
    int total_tasks;            //!< Using for save total number of  tasks.

    Message resp;               //!< Using for save response or command.
    Message::STATUS status;     //!< Using for save currant status.
    int task;                   //!< Using for save current task.

    /*! 
        \brief Preparing command message to Server.
        \param Message* rcvd - Pointer to received message from Server.
        \return void.
    */ 
    virtual void Command(Message* rcvd) = 0;

    /*! 
        \brief Preparing response message to Server.
        \param Message* rcvd - Pointer to received message from Server.
        \return void.
    */ 
    virtual void Response(Message* rcvd) = 0;

public:
    BaseResponse(int serial_number, int total_tasks, int first_task = 0);
    
    //! \brief Class destructor.
    virtual ~BaseResponse() {};

    /*! 
        \brief Processing message.
        \param Message* rcvd - Pointer to received message from Server.
        \return void.
    */ 
    virtual void Processing(Message* rcvd) = 0;

    Message::STATUS GetStatus();
    int GetTask();
    Message GetResponce();
    void SetStatus(Message::STATUS status);
};

#endif // BASERESPONSE_H