#include "ClientResponse.h"

ClientResponse::ClientResponse(int _serial_number, int _number_of_tasks)
    : resp(Message::ACTION::RESPONSE, Message::STATUS::ACCEPTED, 0, _serial_number)
{
    number_of_tasks = _number_of_tasks;
}

ClientResponse::~ClientResponse() {

}

void ClientResponse::Processing(Message* rcvd, int task, Message::STATUS status){
	switch(rcvd->action) {
	    case Message::ACTION::COMMAND: {
	    	Command(rcvd, task, status);
	    	break;
	    }
        case Message::ACTION::RESPONSE: {
//        	response->task = task;
//        	std::cout << ">> Set task #" << task << std::endl;

	    	Response(rcvd, task, status);
        	break;
        }
        default: std::cout << "UNKNOWN ACTION TYPE" << std::endl; break;
	}
}

void ClientResponse::Command(Message* rcvd, int _task, Message::STATUS _status) {
    switch(_status) {
        case Message::STATUS::BUSY: 
        case Message::STATUS::ERROR: {
			resp.Response(_status, _task);
			break;
        }
        case Message::STATUS::DONE:
        case Message::STATUS::READY: {
			resp.Response(Message::STATUS::ACCEPTED, rcvd->task);
        	current_task    = rcvd->task;
			current_status  = Message::STATUS::BUSY;
			break;
		}	
        case Message::STATUS::ACCEPTED: {	 
            std::cout << "ACCEPTED" << std::endl; 	
            break;
        }
        default: {
            std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				
            break;
        }
    }
}

void ClientResponse::Response(Message* rcvd, int _task, Message::STATUS _status) {
    switch(rcvd->status) {
        case Message::STATUS::BUSY: 
        case Message::STATUS::ERROR: {
			resp.Response(Message::STATUS::ACCEPTED, rcvd->task);
			break;
        }
        case Message::STATUS::DONE:
        case Message::STATUS::READY: 
        case Message::STATUS::ACCEPTED: {
            if(_task == number_of_tasks) {
			    resp.Response(Message::STATUS::ACCEPTED, rcvd->task);
            } else {
            	std::cout << ">> Send to server task #" << _task << std::endl;
                resp.Command(Message::STATUS::READY, _task);
            }
			break;
		}	
        default: { 
            std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				
            break;
        }
    }
}
