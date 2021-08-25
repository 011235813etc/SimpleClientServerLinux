#include "Message.h"

Message::Message():action(ACTION::RESPONSE), status(STATUS::READY), task(0), sender(0)  {
}
    
Message::Message(const ACTION _action, const STATUS _status, const int _task, const int _sender)
        :action(_action), status(_status), task(_task), sender(_sender) {
}

Message::Message(const Message& other) {
   if (this != &other) {   
        action 	= other.action;
        status 	= other.status;
        task 	= other.task;
        sender 	= other.sender;
   }
}

Message& Message::operator=(Message&& other) {
   if (this != &other) {   
        action 	= other.action;
        status 	= other.status;
        task 	= other.task;
        sender 	= other.sender;
   }
   return *this;
}

bool Message::operator==(const Message& msg) {
    return (this->action == msg.action  ||
            this->status == msg.status  ||
            this->task  == msg.task     ||
            this->sender == msg.sender  );
}

void Message::Response(Message::STATUS _status, int _task) {
	action = ACTION::RESPONSE;
	status = _status;
    task   = _task;
}

void Message::Command(Message::STATUS _status, int _task) {
	action = ACTION::COMMAND;
	status = _status;
    task   = _task;
}

std::ostream& operator<<(std::ostream& os, const Message& msg) {

    using namespace std;

    cout << "sender: "	<< msg.sender 	<< endl;
    cout << msg.action  << endl;
    cout << msg.status  << endl;
    cout << "task: "  	<< msg.task   	<< endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Message::ACTION& action) {

    os << "action: ";
    switch(action) {
        case Message::ACTION::COMMAND:   os << "COMMAND";          break;
        case Message::ACTION::RESPONSE:  os << "RESPONSE";         break;
        default:                         os << "UNKNOWN ACTION";   break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Message::STATUS& status) {

    os << "status: ";
    switch(status) {
        case Message::STATUS::DONE:      os << "DONE";             	break;
        case Message::STATUS::ERROR:     os << "ERROR";            	break;
        case Message::STATUS::BUSY:      os << "BUSY";             	break;
        case Message::STATUS::READY:     os << "READY";            	break;
        case Message::STATUS::ACCEPTED:	 os << "ACCEPTED";			break;
        default:                         os << "UNKNOWN STATUS";   	break;
    }
    return os;
}
