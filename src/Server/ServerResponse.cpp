/*! \file ServerResponse.cpp
    \brief ServerResponse class implementation.

    This class describe preparing response for Client.
*/

#include "ServerResponse.h"

/*! 
    \brief Constructor with argument.
    \param int serial_number - Client serial number
*/ 
ServerResponse::ServerResponse(int serial_number)
    : BaseResponse(serial_number, 0, 0)
{
}

/*! 
    \brief Class destructor.

	Free the task queue.
*/
ServerResponse::~ServerResponse() {
	while(!task_queue.empty())	{
		task_queue.pop();
	}
}

/*! 
    \brief Processing message from Client.
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::Processing(Message* from_client) {
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

/*! 
    \brief Preparing command message to Client.
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::Command(Message* from_client) {
    
    switch(from_client->status) {
		case Message::STATUS::DONE: {
			response.Response(Message::STATUS::ACCEPTED, from_client->task);
			SaveCommand(from_client->task);
			std::cout << "Server is ready for execute tasks!" << std::endl;
			isAllCommandsReceived = true;			
			break;
		}
		case Message::STATUS::ERROR: {
			std::cout << "ERROR!" << std::endl; 
			std::cout << "Task steak will be cleared!" << std::endl; 	
			while(!task_queue.empty())	{
				std::cout << task_queue.front() << std::endl;
				task_queue.pop();
			}
			break;
		}
        case Message::STATUS::BUSY:
        case Message::STATUS::READY: 
        case Message::STATUS::ACCEPTED: {
			response.Response(Message::STATUS::ACCEPTED, from_client->task);
			SaveCommand(from_client->task);
			break;
		}
        default: { 
			std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				
			break;
		}
    }
}

/*! 
    \brief Preparing response message to Client.
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::Response(Message* from_client) {
    switch(from_client->status) {
       	case Message::STATUS::DONE:
		case Message::STATUS::READY: {
			if(isAllCommandsReceived) {
				if(!task_queue.empty()) {
					std::cout << ">> Set to client task #" << task_queue.front() << std::endl;
					response.Command(Message::STATUS::READY, task_queue.front());
					task_queue.pop();
				} else {
					std::cout << "Task stack empty" << std::endl;
					response.Response(Message::STATUS::DONE, from_client->task);
				}
			} else {
				response.Response(Message::STATUS::BUSY, Message::launch_task);
			}
			break;
		}	
		case Message::STATUS::BUSY: {
			response.Response(Message::STATUS::ACCEPTED, task_queue.front());
			break;
		}
		case Message::STATUS::ACCEPTED:	{ 
			std::cout << "ACCEPTED" << std::endl; 	
			break;
		}
		default: {
			std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				
			break;
		}
    }
}

/*! 
    \brief Saving commands from Client.
    \param int task - task number.
	\return void.
*/ 
void ServerResponse::SaveCommand(int task) {
	task_queue.push(task);
}

/*! 
    \brief Set commands load complete status (use only unit tests).
    \param bool complete - commands load status.
	\return void.
*/ 
void ServerResponse::SetCommandsLoadComplete(bool complete) {
	isAllCommandsReceived = complete;
}