#include "BaseResponse.h"

BaseResponse::BaseResponse(int serial_number, int total_tasks, int first_task)
    : resp(Message::ACTION::RESPONSE, Message::STATUS::ACCEPTED, first_task, serial_number)
{
    task = first_task;
    this->total_tasks = total_tasks;
}

void BaseResponse::Processing(Message* rcvd) {

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
