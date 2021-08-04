#include "ServerResponse.h"

ServerResponse::ServerResponse(int _serial_number)
    : resp(Message::ACTION::RESPONSE, Message::STATUS::ACCEPTED, 0, _serial_number)
{
}

ServerResponse::~ServerResponse() {

}

void ServerResponse::Processing(Message* rcvd, Message::STATUS status){
	switch(rcvd->action) {
	    case Message::ACTION::COMMAND: {
	    	Command(rcvd, status);
	    	break;
	    }
        case Message::ACTION::RESPONSE: {
	    	Response(rcvd, status);
        	break;
        }
        default: std::cout << "UNKNOWN ACTION TYPE" << std::endl; break;
	}
}

void ServerResponse::Command(Message* rcvd, Message::STATUS _status) {
    
    switch(rcvd->status) {
		case Message::STATUS::DONE: {
			resp.Response(Message::STATUS::ACCEPTED, rcvd->task);
        	task_stack.push(rcvd->task);
			std::cout << "Server is ready for execute tasks!" << std::endl; 			
			break;
		}
		case Message::STATUS::ERROR: {
			std::cout << "ERROR!" << std::endl; 
			std::cout << "Task steak will be cleared!" << std::endl; 	
			while(!task_stack.empty())	{
				std::cout << task_stack.top() << std::endl;
				task_stack.pop();
			}
			break;
		}
        case Message::STATUS::BUSY:
        case Message::STATUS::READY: 
        case Message::STATUS::ACCEPTED: {
			resp.Response(Message::STATUS::ACCEPTED, rcvd->task);
        	task_stack.push(rcvd->task);
			break;
		}
        default: { 
			std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				
			break;
		}
    }
}

void ServerResponse::Response(Message* rcvd, Message::STATUS _status) {
    switch(rcvd->status) {
       	case Message::STATUS::DONE:
		case Message::STATUS::READY: {
			std::cout << ">> Set to client task #" << task_stack.top() << std::endl;
			resp.Command(Message::STATUS::READY, task_stack.top());
			break;
		}	
		case Message::STATUS::ERROR: {
			std::cout << "ERROR!" << std::endl; 		
			break;
		}
		case Message::STATUS::BUSY: {
			resp.Response(Message::STATUS::ACCEPTED, task_stack.top());
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
