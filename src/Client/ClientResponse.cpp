#include "ClientResponse.h"

ClientResponse::ClientResponse(int _serial_number, int _number_of_tasks, int first_task)
    : resp(Message::ACTION::RESPONSE, Message::STATUS::ACCEPTED, first_task, _serial_number)
{
    task = first_task;
    number_of_tasks = _number_of_tasks;
}

ClientResponse::~ClientResponse() {

}

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

void ClientResponse::Command(Message* rcvd) {
    resp.Response(Message::STATUS::ACCEPTED, rcvd->task);
    task    = rcvd->task;
    status  = Message::STATUS::BUSY;
}

void ClientResponse::Response(Message* rcvd) {
    switch(rcvd->status) {
        case Message::STATUS::BUSY: {
            //TODO need to repeat command after few seconds
			resp.Response(Message::STATUS::ACCEPTED, rcvd->task);
			break;
        }
        case Message::STATUS::ACCEPTED: {
            std::cout << ">> Send to server task #" << ++task << std::endl;
            if(rcvd->task == number_of_tasks - 1) {
			    resp.Command(Message::STATUS::DONE, task);
            } else {
                resp.Command(Message::STATUS::ACCEPTED, task);
            }
			break;
		}	
        default: { 
            std::cout << "UNKNOWN STATUS TYPE" << std::endl; 				
            break;
        }
    }
}
