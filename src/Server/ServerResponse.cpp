#include "ServerResponse.h"

ServerResponse::ServerResponse(int serial_number)
    : BaseResponse(serial_number, 0, 0)
{
}

ServerResponse::~ServerResponse() {
	while(!task_queue.empty())	{
		task_queue.pop();
	}
}

void ServerResponse::Processing(Message* rcvd) {
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

void ServerResponse::Command(Message* rcvd) {
    
    switch(rcvd->status) {
		case Message::STATUS::DONE: {
			resp.Response(Message::STATUS::ACCEPTED, rcvd->task);
			SaveCommand(rcvd->task);
			std::cout << "Server is ready for execute tasks!" << std::endl; 			
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
			resp.Response(Message::STATUS::ACCEPTED, rcvd->task);
			SaveCommand(rcvd->task);
			break;
		}
        default: { 
			std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				
			break;
		}
    }
}

void ServerResponse::Response(Message* rcvd) {
    switch(rcvd->status) {
       	case Message::STATUS::DONE:
		case Message::STATUS::READY: {
			if(!task_queue.empty()) {
				std::cout << ">> Set to client task #" << task_queue.front() << std::endl;
				resp.Command(Message::STATUS::READY, task_queue.front());
				task_queue.pop();
			} else {
				std::cout << "Task stack empty" << std::endl;
				resp.Response(Message::STATUS::DONE, rcvd->task);
			}
			break;
		}	
		case Message::STATUS::BUSY: {
			resp.Response(Message::STATUS::ACCEPTED, task_queue.front());
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
