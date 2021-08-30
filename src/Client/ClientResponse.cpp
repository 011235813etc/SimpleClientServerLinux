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
    \param Message* from_client - Pointer to received message from Server.
*/ 
void ClientResponse::Processing(Message* from_client) {

    if(status == Message::STATUS::BUSY) {
        response.Response(status, from_client->task);
    } else {
        switch(from_client->action) {
            case Message::ACTION::COMMAND: {
                Command(from_client);
                break;
            }
            case Message::ACTION::RESPONSE: {
                Response(from_client);
                break;
            }
            default: std::cout << "UNKNOWN ACTION TYPE" << std::endl; break;
        }
    }
}

/*! 
    \brief Preparing command message to Server.
    \param Message* from_client - Pointer to received message from Server.
*/ 
void ClientResponse::Command(Message* from_client) {
    response.Response(Message::STATUS::ACCEPTED, from_client->task);
    task    = from_client->task;
    status  = Message::STATUS::BUSY;
}

/*! 
    \brief Preparing response message to Server.
    \param Message* from_client - Pointer to received message from Server.
*/ 
void ClientResponse::Response(Message* from_client) {
    switch(from_client->status) {
        case Message::STATUS::BUSY: {
            //waiting 1 sec
            const uint8_t one_sec = 1;
            std::chrono::seconds dura(one_sec);
            std::this_thread::sleep_for(dura);
			response.Response(Message::STATUS::READY, from_client->task);
            //TODO make limit for request
			break;
        }
        case Message::STATUS::ACCEPTED: {
            std::cout << ">> Send to server task #" << ++task << std::endl;
            if(from_client->task == total_tasks - 1) {
			    response.Command(Message::STATUS::DONE, task);
            } else {
                response.Command(Message::STATUS::ACCEPTED, task);
            }
			break;
		}	
        case Message::STATUS::DONE: {
            std::cout << "Tasks done" << std::endl;
            response.Response(Message::STATUS::DONE, Message::done_task);
            status = Message::STATUS::DONE;     
            task = Message::done_task;                   
			break;
		}	
        default: { 
            std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				
            break;
        }
    }
}
