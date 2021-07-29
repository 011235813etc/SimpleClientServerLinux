#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>

class Message {
public:
	enum class ACTION : uint8_t { COMMAND, RESPONSE 		};
    enum class STATUS : uint8_t { DONE, ERROR, BUSY, READY 	};

    friend std::ostream& operator<<(std::ostream& os, const ACTION& action);
    friend std::ostream& operator<<(std::ostream& os, const STATUS& status);
    friend std::ostream& operator<<(std::ostream& os, const Message& msg);

    ACTION action;
    STATUS status;
    int task;
    int serial_number;

    Message() {
        action = ACTION::RESPONSE;
        status = STATUS::READY;
        task = 0;
        serial_number = 0;
    }
    
    Message(const ACTION _action, const STATUS _status, const int _task, int _serial_number) {
        status 	= _status;
        action 	= _action;
        task 	= _task;
        serial_number = _serial_number;
    }
    
    void SetStatus(const STATUS _status)	{ status 	= _status; 	}
    void SetAction(const ACTION _action)	{ action 	= _action; 	}
    void SetTask(const int _task)			{ task 		= _task; 	}
};

#endif // MESSAGE_H
