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
}

/*! 
    \brief Processing message from Server.
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::Processing(Message* from_server) {

    if(status == Message::STATUS::BUSY) {
        response.Response(status, from_server->task);
    } else {
        switch(from_server->action) {
            case Message::ACTION::COMMAND:  { Command(from_server);     break; }
            case Message::ACTION::RESPONSE: { Response(from_server);    break; }
            default: std::cout << "UNKNOWN ACTION TYPE" << std::endl;   break;
        }
    }
}

/*! 
    \brief Preparing command message to Server.
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::Command(Message* from_server) {
    switch(status) {
        case Message::STATUS::BUSY:     { CommandServerBusy(from_server);       break; }
        case Message::STATUS::READY:    { CommandServerReady(from_server);      break; }	
        case Message::STATUS::ACCEPTED: { CommandServerAccepted(from_server);   break; }	
        case Message::STATUS::DONE:     { CommandServerDone(from_server);       break; }	
        default: { std::cout << "UNKNOWN STATUS TYPE" << std::endl;             break; }
    }
}

/*! 
    \brief Preparing response message to Server.
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::Response(Message* from_server) {
    switch(from_server->status) {
        case Message::STATUS::BUSY:     { ResponseServerBusy(from_server);      break; }
        case Message::STATUS::READY:    { ResponseServerReady(from_server);     break; }	
        case Message::STATUS::ACCEPTED: { ResponseServerAccepted(from_server);  break; }	
        case Message::STATUS::DONE:     { ResponseServerDone(from_server);      break; }	
        default: { std::cout << "UNKNOWN STATUS TYPE" << std::endl; 			break; }
    }
}
////////////////////////////////////////////////////////////////////////////////
/*! 
    \brief Prepare response for command from server with status "BUSY".
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::CommandServerBusy(Message* from_server) {
    std::cout << "Nothing here. Fix it!" << std::endl;
}

/*! 
    \brief Prepare response for command from server with status "READY".
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::CommandServerReady(Message* from_server) {
    response.Response(Message::STATUS::ACCEPTED, from_server->task);
    task    = from_server->task;
    status  = Message::STATUS::BUSY;
}

/*! 
    \brief Prepare response for command from server with status "ACCEPTED".
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::CommandServerAccepted(Message* from_server) {
    std::cout << "Nothing here. Fix it!" << std::endl;
}

/*! 
    \brief Prepare response for command from server with status "DONE".
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::CommandServerDone(Message* from_server) {
    std::cout << "Nothing here. Fix it!" << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
/*! 
    \brief Prepare response for response from server with status "BUSY".
    \param Message* from_server - Pointer to received message from Server.
*/ 
void ClientResponse::ResponseServerBusy(Message* from_server) {
    //waiting 1 sec
    const uint8_t one_sec = 1;
    std::chrono::seconds dura(one_sec);
    std::this_thread::sleep_for(dura);
    response.Response(Message::STATUS::READY, from_server->task);
    //TODO make limit for request
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
        }
    } else {
        std::cout << "Need to do smth" << std::endl; 

        // std::cout << ">> Send to server task #" << ++task << std::endl;
        task++;
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
            response.Command(Message::STATUS::READY, task);
            std::cout << "<< Send to server task #" << task << std::endl;
        } else {
            response.Command(Message::STATUS::DONE, task);
            std::cout << "Task #" << task << " is last." << std::endl;
        }
    } else {
        response.Command(Message::STATUS::ACCEPTED, task);
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
        response.Response(Message::STATUS::READY, Message::launch_task);
    } else {
        std::cout << "Tasks done" << std::endl;
        response.Response(Message::STATUS::DONE, Message::done_task);
        status = Message::STATUS::DONE;     
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
        response.Response(Message::STATUS::READY, task);
    } else {
        response.Response(Message::STATUS::DONE, task);
        status = Message::STATUS::READY;
    }
}

/*! 
    \brief Get status of completing all tasks.
    \return bool - status of completing all tasks.
*/
bool ClientResponse::IsTasksDone() {
    return (task == Message::done_task);
}