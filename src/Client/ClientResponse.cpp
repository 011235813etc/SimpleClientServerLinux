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
    loadingTasks = false;
    isNeedResponse = true;
}

//! \brief Copy constructor.
//! \param const ClientResponse& other - other object of class Message. 
ClientResponse::ClientResponse(const ClientResponse& other) : BaseResponse(other) {
	if (this != &other) {  
		loadingTasks = other.loadingTasks;
        isNeedResponse = other.isNeedResponse;
	}
}

//! \brief Copy assignment operator.
//! \param const ClientResponse& other - other object of class Message. 
//! \return ClientResponse& - current object
ClientResponse& ClientResponse::operator=(const ClientResponse& other) {
	BaseResponse::operator=(other);
   if (this != &other) {   
		loadingTasks = other.loadingTasks;
        isNeedResponse = other.isNeedResponse;
   }
   return *this;
}

//! \brief Copy assignment operator.
//! \param const ClientResponse&& other - other object of class Message. 
//! \return ClientResponse& - current object
ClientResponse& ClientResponse::operator=(const ClientResponse&& other) {
	BaseResponse::operator=(other);
   if (this != &other) {   
		loadingTasks = other.loadingTasks;
        isNeedResponse = other.isNeedResponse;
   }
   return *this;
}

/*! 
    \brief Processing message from Server.
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::Processing(Message* from_server) {

    isNeedResponse = true;
    if(status == STATUS::BUSY) {
        response.Response(status, from_server->task);
    } else {
        switch(from_server->action) {
            case ACTION::COMMAND:  { Command(from_server);     break; }
            case ACTION::RESPONSE: { Response(from_server);    break; }
            default: { 
			    std::cout << "Request from server with " << from_server->action << std::endl;
                isNeedResponse = false;
			    break; 
		    }
        }
    }
}

/*! 
    \brief Preparing command message to Server.
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::Command(Message* from_server) {
    switch(from_server->status) {
        case STATUS::READY:    { CommandServerReady(from_server);      break; }	
        default: { 
			std::cout << "Command from server with " << from_server->status << std::endl;
            isNeedResponse = false;
			break; 
		}
    }
}

/*! 
    \brief Preparing response message to Server.
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::Response(Message* from_server) {
    switch(from_server->status) {
        case STATUS::DONE:     { ResponseServerDone(from_server);      break; }	
        case STATUS::BUSY:     { ResponseServerBusy(from_server);      break; }
        case STATUS::READY:    { ResponseServerReady(from_server);     break; }	
        case STATUS::ACCEPTED: { ResponseServerAccepted(from_server);  break; }	
        default: { 
			std::cout << "Response from server with " << from_server->status << std::endl;
            isNeedResponse = false;
			break; 
		}
    }
}
////////////////////////////////////////////////////////////////////////////////
/*! 
    \brief Prepare response for command from server with status "READY".
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::CommandServerReady(Message* from_server) {
    response.Response(STATUS::ACCEPTED, from_server->task);
    task    = from_server->task;
    status  = STATUS::BUSY;
}

////////////////////////////////////////////////////////////////////////////////
/*! 
    \brief Prepare response for response from server with status "BUSY".
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::ResponseServerBusy(Message* from_server) {

    static uint8_t count = 0;
    const uint8_t one_sec = 1;

    if(count++ < 2) {
        //waiting 1 sec
        std::chrono::seconds dura(one_sec);
        std::this_thread::sleep_for(dura);
        response.Response(STATUS::READY, from_server->task);
    } else {
        std::cout << "Server is busy!" << std::endl;
        isNeedResponse = false;
    }
}

/*! 
    \brief Prepare response for response from server with status "READY".
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::ResponseServerReady(Message* from_server) {
    if(from_server->task == Message::launch_task) {
        loadingTasks = (task == Message::launch_task);
        if(loadingTasks) {
            ResponseServerAccepted(from_server);
        } else {
            std::cout << "Server is ready" << std::endl; 
            isNeedResponse = false;  
        }
    } else {
        // std::cout << "Need to do smth" << std::endl; 
        // task++;
        std::cout << "Server is ready" << std::endl; 
        isNeedResponse = false;
    }
}

/*! 
    \brief Prepare response for response from server with status "ACCEPTED".
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::ResponseServerAccepted(Message* from_server) {

    if(loadingTasks) {
        task = (from_server->task == Message::launch_task) ? 0 : from_server->task + 1;

        if(task + 1 < total_tasks) {
            response.Command(STATUS::READY, task);
            std::cout << "<< Send to server task #" << task << std::endl;
        } else {
            response.Command(STATUS::DONE, task);
            std::cout << "Task #" << task << " is last." << std::endl;
        }
    } else {
        // response.Command(STATUS::ACCEPTED, task);
        isNeedResponse = false;
    }
}

/*! 
    \brief Prepare response for response from server with status "DONE".
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::ResponseServerDone(Message* from_server) {

    if(loadingTasks) {
        loadingTasks = false;
        task = Message::launch_task;
        isNeedResponse = false;
    } else {
        std::cout << "Tasks done" << std::endl;
        response.Response(STATUS::DONE, Message::done_task);
        status = STATUS::DONE;     
        task = Message::done_task; 
    }
}
////////////////////////////////////////////////////////////////////////////////

/*! 
    \brief Get tasks loading status to server.
    \return bool - loading status.
*/ 
bool ClientResponse::IsLoading() {
     return loadingTasks;
} 

/*! 
    \brief Create request to server for get commands.
    \return void.
*/
void ClientResponse::RequestCommandFromServer() {
    if(task == Message::launch_task) {
        response.Response(STATUS::READY, task);
    } else {
        response.Response(STATUS::DONE, task);
        status = STATUS::READY;
    }
}

/*! 
    \brief Get status of completing all tasks.
    \return bool - status of completing all tasks.
*/
bool ClientResponse::IsTasksDone() {
    return (task == Message::done_task);
}

