//! \file ServerResponse.cpp
//! \brief ServerResponse class implementation.
//! This class describe preparing response for Client.

#include "ServerResponse.h"

//! \brief Constructor with argument.
//! \param int serial_number - Client serial number
ServerResponse::ServerResponse(int serial_number) : BaseResponse(serial_number, 0, 0) {
    isAcceptingCommands = false;
}

//! \brief Copy constructor.
//! \param const ServerResponse& other - other object of class Message. 
ServerResponse::ServerResponse(const ServerResponse& other) : BaseResponse(other) {
	
	if (this != &other) {  
		isAcceptingCommands = other.isAcceptingCommands;
	}
}

//! \brief Copy assignment operator.
//! \param const ServerResponse& other - other object of class Message. 
//! \return ServerResponse& - current object
ServerResponse& ServerResponse::operator=(const ServerResponse& other) {
	BaseResponse::operator=(other);
   if (this != &other) {   
		isAcceptingCommands = other.isAcceptingCommands;
   }
   return *this;
}

//! \brief Copy assignment operator.
//! \param const ServerResponse&& other - other object of class Message. 
//! \return ServerResponse& - current object
ServerResponse& ServerResponse::operator=(const ServerResponse&& other) {
	BaseResponse::operator=(other);
   if (this != &other) {   
		isAcceptingCommands = other.isAcceptingCommands;
   }
   return *this;
}
 
//! \brief Class destructor.
//! Free the task queue.
ServerResponse::~ServerResponse() {
	while(!task_queue.empty())	{
		task_queue.clear();
	}
}
 
//! \brief Processing message from Client.
//! \param Message* from_client - Pointer to received message from Client.
//! \return void.
void ServerResponse::Processing(Message* from_client) {
	isNeedResponse = true;
	switch(from_client->action) {
	    case ACTION::COMMAND: 	{ Command(from_client);  break; }
        case ACTION::RESPONSE: 	{ Response(from_client); break; }
		default: { 
			std::cout << "Request from client with " << from_client->action << std::endl;
			isNeedResponse = false;
			break; 
		}
	}
}

 
//! \brief Preparing command message to Client.
//! \param Message* from_client - Pointer to received message from Client.
//! \return void.
void ServerResponse::Command(Message* from_client) {
    switch(from_client->status) {
		case STATUS::DONE: 	{ CommandClientDone(from_client);  		break; }
		case STATUS::ERROR: { CommandClientError(from_client); 		break; }
        case STATUS::READY: { CommandClientReady(from_client); 		break; }
        default: { 
			std::cout << "Command from client with " << from_client->status << std::endl;
			isNeedResponse = false;
			break; 
		}
    }
}

//! \brief Preparing response message to Client.
//! \param Message* from_client - Pointer to received message from Client.
//! \return void.
void ServerResponse::Response(Message* from_client) {
    switch(from_client->status) {
       	case STATUS::DONE: 		{ ResponseClientDone(from_client); 		break; }
		case STATUS::READY: 	{ ResponseClientReady(from_client); 	break; }	
		default: { 
			std::cout << "Response from client with " << from_client->status << std::endl;
			isNeedResponse = false;
			break; 
		}
    }
}

 
//! \brief Saving commands from Client.
//! \param int task - task number.
//! \return void.
void ServerResponse::SaveCommand(int task) {
	task_queue.push_front(task);
}

////////////////////////////////////////////////////////////////////////////////
 
//! \brief Prepare response for command from client with status "DONE".
//! \param Message* from_client - Pointer to received message from Client.
//! \return void.
void ServerResponse::CommandClientDone(Message* from_client) {
	response.Response(STATUS::DONE, from_client->task);
	SaveCommand(from_client->task);
	std::cout << "Server is ready for execute tasks!" << std::endl;
	isAcceptingCommands = false;
}

 
//! \brief Prepare response for command from client with status "ERROR".
//! \param Message* from_client - Pointer to received message from Client.
//! \return void.
void ServerResponse::CommandClientError(Message* from_client) {
	std::cout << "ERROR!" << std::endl; 
	std::cout << "Task steak will be cleared!" << std::endl; 	
	while(!task_queue.empty())	{
		std::cout << "Delete task #" << task_queue.front() << std::endl;
		task_queue.pop_front();
	}
	response.Response(STATUS::DONE, Message::launch_task);
}

 
//! \brief Prepare response for command from client with status "READY".
//! \param Message* from_client - Pointer to received message from Client.
//! \return void.
void ServerResponse::CommandClientReady(Message* from_client) {
	isAcceptingCommands = true;
	if(from_client->task == Message::launch_task) {
		response.Response(STATUS::READY, from_client->task);
	} else {
		response.Response(STATUS::ACCEPTED, from_client->task);
		SaveCommand(from_client->task);
	}
}

////////////////////////////////////////////////////////////////////////////////

 
//! \brief Prepare response for response from client with status "DONE".
//! \param Message* from_client - Pointer to received message from Client.
//! \return void.
void ServerResponse::ResponseClientDone(Message* from_client) {
	if(!isAcceptingCommands) {
		if(task < task_queue.size()) {
			std::cout << ">> Set to client task #" << task_queue[task] << std::endl;
			response.Command(STATUS::READY, task_queue[task]);
			task++;
		} else {
			std::cout << "Task stack empty" << std::endl;
			response.Response(STATUS::DONE, Message::done_task);
		}
	} else {
		isNeedResponse = false;
	}
}

 
//! \brief Prepare response for response from client with status "READY".
//! \param Message* from_client - Pointer to received message from Client.
//! \return void.
void ServerResponse::ResponseClientReady(Message* from_client) {
	if(isAcceptingCommands) {
		response.Response(STATUS::BUSY, Message::launch_task);
	} else {
		ResponseClientDone(from_client);
	}
}
////////////////////////////////////////////////////////////////////////////////

