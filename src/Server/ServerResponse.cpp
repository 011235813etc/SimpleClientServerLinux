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
    isAcceptingCommands = false;
	isNeedResponse = true;
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
		case Message::STATUS::DONE: 	{ CommandClientDone(from_client); 		break; }
		case Message::STATUS::ERROR: 	{ CommandClientError(from_client); 		break; }
        case Message::STATUS::READY:  	{ CommandClientReady(from_client); 		break; }
        case Message::STATUS::BUSY:		{ CommandClientBusy(from_client); 		break; }
        case Message::STATUS::ACCEPTED: { CommandClientAccepted(from_client); 	break; }
        default: { std::cout << "UNKNOWN STATUS TYPE" << std::endl; break; }
    }
}

/*! 
    \brief Preparing response message to Client.
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::Response(Message* from_client) {
    switch(from_client->status) {
       	case Message::STATUS::DONE: 	{ ResponseClientDone(from_client); break;		}
		case Message::STATUS::ERROR: 	{ ResponseClientError(from_client); break; 		}
		case Message::STATUS::READY: 	{ ResponseClientReady(from_client); break; 		}	
		case Message::STATUS::BUSY: 	{ ResponseClientBusy(from_client); break; 		}
		case Message::STATUS::ACCEPTED:	{ ResponseClientAccepted(from_client); break; 	}
		default: { std::cout << "UNKNOWN STATUS TYPE" << std::endl; break; }
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
    \brief Set accepting commands status (use only unit tests).
    \param bool complete - commands load status.
	\return void.
*/ 
void ServerResponse::SetAcceptingCommands(bool accepting) {
	isAcceptingCommands = accepting;
}

////////////////////////////////////////////////////////////////////////////////
/*! 
    \brief Prepare response for command from client with status "DONE".
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::CommandClientDone(Message* from_client) {
	response.Response(Message::STATUS::DONE, from_client->task);
	SaveCommand(from_client->task);
	std::cout << "Server is ready for execute tasks!" << std::endl;
	isAcceptingCommands = false;
}

/*! 
    \brief Prepare response for command from client with status "ERROR".
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::CommandClientError(Message* from_client) {
	std::cout << "ERROR!" << std::endl; 
	std::cout << "Task steak will be cleared!" << std::endl; 	
	while(!task_queue.empty())	{
		std::cout << task_queue.front() << std::endl;
		task_queue.pop();
	}
}

/*! 
    \brief Prepare response for command from client with status "ACCEPTED".
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::CommandClientAccepted(Message* from_client) {
	response.Response(Message::STATUS::ACCEPTED, from_client->task);
}

/*! 
    \brief Prepare response for command from client with status "BUSY".
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::CommandClientBusy(Message* from_client) {
	std::cout << "Nothing here. Fix it!" << std::endl;
}

/*! 
    \brief Prepare response for command from client with status "READY".
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::CommandClientReady(Message* from_client) {
	if(from_client->task == Message::launch_task) {
		response.Response(Message::STATUS::READY, from_client->task);
		isAcceptingCommands = true;
	} else {
		response.Response(Message::STATUS::ACCEPTED, from_client->task);
		SaveCommand(from_client->task);
	}
}

////////////////////////////////////////////////////////////////////////////////

/*! 
    \brief Prepare response for response from client with status "DONE".
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::ResponseClientDone(Message* from_client) {
	if(!isAcceptingCommands) {
		if(!task_queue.empty()) {
			std::cout << ">> Set to client task #" << task_queue.front() << std::endl;
			response.Command(Message::STATUS::READY, task_queue.front());
			task_queue.pop();
		} else {
			std::cout << "Task stack empty" << std::endl;
			// response.Response(Message::STATUS::DONE, from_client->task);
			response.Response(Message::STATUS::DONE, Message::done_task);
		}
	} 
}

/*! 
    \brief Prepare response for response from client with status "ERROR".
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::ResponseClientError(Message* from_client) {
	std::cout << "Nothing here. Fix it!" << std::endl; 
}

/*! 
    \brief Prepare response for response from client with status "ACCEPTED".
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::ResponseClientAccepted(Message* from_client) {
	std::cout << "ACCEPTED" << std::endl; 
	isNeedResponse = false;	
}

/*! 
    \brief Prepare response for response from client with status "BUSY".
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::ResponseClientBusy(Message* from_client) {
	response.Response(Message::STATUS::ACCEPTED, task_queue.front());
}

/*! 
    \brief Prepare response for response from client with status "READY".
    \param Message* from_client - Pointer to received message from Client.
	\return void.
*/ 
void ServerResponse::ResponseClientReady(Message* from_client) {
	if(!isAcceptingCommands) {
		ResponseClientDone(from_client);
	} else {
		response.Response(Message::STATUS::BUSY, Message::launch_task);
	}
}
////////////////////////////////////////////////////////////////////////////////

bool ServerResponse::IsNeedResponse() {
	auto need = isNeedResponse;
	isNeedResponse = true;
	return need;
}