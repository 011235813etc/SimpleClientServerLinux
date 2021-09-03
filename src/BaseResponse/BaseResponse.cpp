/*! \file BaseResponse.h
    \brief BaseResponse class implementation.

    This class describe response format.
*/
#include "BaseResponse.h"

/*! 
    \brief Constructor with arguments.
    \param int serial_number - Client serial number
    \param int total_tasks - Total number of tasks.
    \param int first_task - Start value of the task.
*/
BaseResponse::BaseResponse(int serial_number, int total_tasks, int first_task)
    : response(Message::ACTION::RESPONSE, Message::STATUS::READY, first_task, serial_number)
{
    task = first_task;    
    this->total_tasks = total_tasks;
    status = Message::STATUS::READY;
}

/*! 
    \brief Get currnet status.
    \return Message - current status.
*/ 
Message::STATUS BaseResponse::GetStatus() { 
    return status;    
}

/*! 
    \brief Get currnet task.
    \return int - current task.
*/ 
int BaseResponse::GetTask() { 
    return task;      
}

/*! 
    \brief Get ready response message.
    \return Message - message for Client or Server.
*/ 
Message BaseResponse::GetResponce() { 
    return response;      
}

/*! 
    \brief Set new status.
    \param Message::STATUS status - new status.
    \return void.
*/ 
void BaseResponse::SetStatus(Message::STATUS status) { 
    this->status = status;    
}