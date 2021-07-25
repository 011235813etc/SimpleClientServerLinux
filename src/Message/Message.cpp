#include "Message.h"

std::ostream& operator<<(std::ostream& os, const Message& msg) {

    using namespace std;

    cout << msg.status      << endl;
    cout << msg.client      << endl;
    cout << msg.target      << endl;
    cout << "task number "  << static_cast<uint64_t>(msg.task_step)   << endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Message::CLIENT_TYPE& client_type) {

    os << "client type: ";
    switch(client_type) {
        case Message::CLIENT_TYPE::COMMON:   os << "COMMON";               break;
        case Message::CLIENT_TYPE::MASTER:   os << "MASTER";               break;
        case Message::CLIENT_TYPE::LOGGER:   os << "LOGGER";               break;
        default:                             os << "UNKNOWN CLIENT TYPE";  break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Message::TARGET& target) {

    os << "target: ";
    switch(target) {
        case Message::TARGET::OWN:       os << "OWN";              break;
        case Message::TARGET::BY_TURNS:  os << "BY_TURNS";         break;
        case Message::TARGET::ALL:       os << "ALL";              break;
        default:                         os << "UNKNOWN TARGET";   break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Message::STATUS& status) {

    os << "status: ";
    switch(status) {
        case Message::STATUS::DONE:      os << "DONE";             break;
        case Message::STATUS::ERROR:     os << "ERROR";            break;
        case Message::STATUS::BUSY:      os << "BUSY";             break;
        case Message::STATUS::READY:     os << "READY";            break;
        case Message::STATUS::COMMAND:   os << "COMMAND";          break;
        case Message::STATUS::RESPONSE:  os << "RESPONSE";         break;
        default:                         os << "UNKNOWN STATUS";   break;
    }
    return os;
}
