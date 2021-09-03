/*! \file Message.cpp
    \brief Message class implementation.

    This class describe message format using for exchange between Client and Server.
*/
#include "Message.h"

/*! 
    \brief Default constructor.
*/
Message::Message():action(ACTION::RESPONSE), status(STATUS::READY), task(0), sender(0)  {
}

/*! 
    \brief Constructor with arguments.
    \param const ACTION _action - type of action for client or server.
    \param STATUS _status - current object status.
    \param const int _task - current task.
    \param const int _sender - serial number of sender.
*/ 
Message::Message(const ACTION _action, const STATUS _status, const int _task, const int _sender)
        :action(_action), status(_status), task(_task), sender(_sender) {
}

/*! 
    \brief Сopy constructor.
    \param const Message& other - other object of class Message.
*/ 
Message::Message(const Message& other) {
    if (this != &other) {   
        action 	= other.action;
        status 	= other.status;
        task 	= other.task;
        sender 	= other.sender;
    }
}

/*! 
    \brief Copy assignment operator.
    \param const Message& other - other object of class Message. 
    \return Message& - current object
*/
Message& Message::operator=(Message&& other) {
   if (this != &other) {   
        action 	= other.action;
        status 	= other.status;
        task 	= other.task;
        sender 	= other.sender;
   }
   return *this;
}

/*! 
    \brief Compare fields of class Message.
    \param const Message& other - compared object of class Message.  
    \return bool - comparison result.
*/
bool Message::operator==(const Message& other) {
    return (this->action    == other.action  ||
            this->status    == other.status  ||
            this->task      == other.task    ||
            this->sender    == other.sender  );
}

/*! 
    \brief Compare fields of class Message.
    \param const Message& m1 - first compared object of class Message. 
    \param const Message& m2 - second compared object of class Message.  
    \return bool - comparison result.
*/
bool operator==(const Message& m1, const Message& m2) {
    return (m1.action    == m2.action  ||
            m1.status    == m2.status  ||
            m1.task      == m2.task    ||
            m1.sender    == m2.sender  );
}

/*! 
    \brief A response preparation.
    \param Message::STATUS status - current object status.
    \param int task - the task for processing.
    \return void.
*/
void Message::Response(Message::STATUS status, int task) {
	action = ACTION::RESPONSE;
	this->status = status;
    this->task   = task;
}

/*! 
    \brief A command preparation.
    \param Message::STATUS _status - current object status.
    \param int _task - the task for processing.
    \return void.
*/
void Message::Command(Message::STATUS status, int task) {
	action = ACTION::COMMAND;
	this->status = status;
    this->task   = task;
}

/*! 
    \brief Print class Message to the ostream.
    \param ostream& os - ostream objects reference.
    \param const Message& msg - printing object of class Message.
    \return ostream& - ostream objects reference.
*/
std::ostream& operator<<(std::ostream& os, const Message& msg) {

    using namespace std;

    cout << "sender: "	<< msg.sender 	<< endl;
    cout << msg.action  << endl;
    cout << msg.status  << endl;
    cout << "task: "  	<< msg.task   	<< endl;
    return os;
}

/*! 
    \brief Print enum class ACTION to the ostream.
    \param ostream& os - ostream objects reference.
    \param const Message::ACTION& action - printing object of enum class ACTION.
    \return ostream& - ostream objects reference.
*/
std::ostream& operator<<(std::ostream& os, const Message::ACTION& action) {

    os << "action: ";
    switch(action) {
        case Message::ACTION::COMMAND:   os << "COMMAND";          break;
        case Message::ACTION::RESPONSE:  os << "RESPONSE";         break;
        default:                         os << "UNKNOWN ACTION";   break;
    }
    return os;
}

/*! 
    \brief Print enum class STATUS to the ostream.
    \param ostream& os - ostream objects reference.
    \param const Message::STATUS& status - printing object of enum class STATUS.
    \return ostream& - ostream objects reference.
*/
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

/*! 
    \brief Set new status (used for unit tests).
    \param const STATUS _status - new status.
    \return void.
*/
void Message::SetStatus(const STATUS status)	{ 
    this->status 	= status; 	
}   

/*! 
    \brief Set new action (used for unit tests).
    \param const ACTION _action - new action.
    \return void.
*/
void Message::SetAction(const ACTION action)	{ 
    this->action 	= action; 	
}   

/*! 
    \brief Set new task (used for unit tests).
    \param const int _task - new task.
    \return void.
*/
void Message::SetTask(const int _task)			{ 
    task = _task; 	
}   
