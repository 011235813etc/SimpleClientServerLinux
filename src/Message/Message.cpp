#include "Message.h"

void Message::Response(Message::STATUS _status, int _sender) {
	action = ACTION::RESPONSE;
	status = _status;
	sender = _sender;
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
