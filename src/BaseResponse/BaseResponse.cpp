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
    task                = first_task;    
    this->total_tasks   = total_tasks;
    status              = Message::STATUS::READY;
    isNeedResponse      = true;
}

//! \brief Copy constructor.
//! \param const BaseResponse& other - other object of class Message. 
BaseResponse::BaseResponse(const BaseResponse& other) {
    if (this != &other) {   
        response    = other.response;
        task        = other.task;    
        total_tasks = other.total_tasks;
        status      = other.status;
    }
}

//! \brief Copy assignment operator.
//! \param const BaseResponse& other - other object of class BaseResponse. 
//! \return BaseResponse&& - current object
BaseResponse& BaseResponse::operator=(const BaseResponse& other) {
   if (this != &other) {   
    response    = other.response;
    task        = other.task;    
    total_tasks = other.total_tasks;
    status      = other.status;
   }
   return *this;
}

//! \brief Copy assignment operator.
//! \param const BaseResponse&& other - other object of class BaseResponse. 
//! \return BaseResponse&& - current object
BaseResponse& BaseResponse::operator=(const BaseResponse&& other) {
   if (this != &other) {   
    response    = other.response;
    task        = other.task;    
    total_tasks = other.total_tasks;
    status      = other.status;
   }
   return *this;
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

//! \brief Get do not need response status.
//! \return bool - do not need response status.
bool BaseResponse::IsNeedResponse() {
	auto need = isNeedResponse;
	isNeedResponse = true;
	return need;
}