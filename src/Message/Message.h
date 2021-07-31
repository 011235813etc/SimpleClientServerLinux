#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>

class Message {
public:
	enum class ACTION : uint8_t { COMMAND, RESPONSE };
    enum class STATUS : uint8_t { DONE, ERROR, BUSY, READY, ACCEPTED };

    friend std::ostream& operator<<(std::ostream& os, const ACTION& action);
    friend std::ostream& operator<<(std::ostream& os, const STATUS& status);
    friend std::ostream& operator<<(std::ostream& os, const Message& msg);

    ACTION action;
    STATUS status;
    int task;
    int sender;

    Message() {
        action 	= ACTION::RESPONSE;
        status 	= STATUS::READY;
        task 	= 0;
        sender 	= 0;
    }
    
    Message(const ACTION _action, 
            const STATUS _status, 
            const int _task, 
            const int _sender) {
        status 	= _status;
        action 	= _action;
        task 	= _task;
        sender 	= _sender;
    }
    
    void SetStatus(const STATUS _status)	{ status 	= _status; 	}
    void SetAction(const ACTION _action)	{ action 	= _action; 	}
    void SetTask(const int _task)			{ task 		= _task; 	}
    
    void Response(Message::STATUS _status, int _sender);
    void Command(Message::STATUS _status, int _sender);
};

#endif // MESSAGE_H
