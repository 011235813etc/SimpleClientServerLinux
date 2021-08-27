/*! \file ClientResponse.cpp
    \brief ClientResponse class implementation.

    This class describe preparing response or command for Server.
    ClientResponse derived BaseResponse.
*/

#include "ClientResponse.h"

/*! 
    \brief Constructor with arguments.
    \param int serial_number - Client serial number
    \param int total_tasks - Total number of tasks.
    \param int first_task - Start value of the task.
*/ 
ClientResponse::ClientResponse(int serial_number, int total_tasks, int first_task)
    : BaseResponse(serial_number, total_tasks, first_task)
{
    
}

/*! 
    \brief Processing message from Server.
    \param Message* rcvd - Pointer to received message from Server.
*/ 
void ClientResponse::Processing(Message* rcvd) {

    if(status == Message::STATUS::BUSY) {
        resp.Response(status, rcvd->task);
    } else {
        switch(rcvd->action) {
            case Message::ACTION::COMMAND: {
                Command(rcvd);
                break;
            }
            case Message::ACTION::RESPONSE: {
                Response(rcvd);
                break;
            }
            default: std::cout << "UNKNOWN ACTION TYPE" << std::endl; break;
        }
    }
}

/*! 
    \brief Preparing command message to Server.
    \param Message* rcvd - Pointer to received message from Server.
*/ 
void ClientResponse::Command(Message* rcvd) {
    resp.Response(Message::STATUS::ACCEPTED, rcvd->task);
    task    = rcvd->task;
    status  = Message::STATUS::BUSY;
}

/*! 
    \brief Preparing response message to Server.
    \param Message* rcvd - Pointer to received message from Server.
*/ 
void ClientResponse::Response(Message* rcvd) {
    switch(rcvd->status) {
        case Message::STATUS::BUSY: {
            //TODO need to repeat command after few seconds
			resp.Response(Message::STATUS::ACCEPTED, rcvd->task);
			break;
        }
        case Message::STATUS::ACCEPTED: {
            std::cout << ">> Send to server task #" << ++task << std::endl;
            if(rcvd->task == total_tasks - 1) {
			    resp.Command(Message::STATUS::DONE, task);
            } else {
                resp.Command(Message::STATUS::ACCEPTED, task);
            }
			break;
		}	
        case Message::STATUS::DONE: {
            std::cout << "Tasks done" << std::endl;
			break;
		}	
        default: { 
            std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				
            break;
        }
    }
}
