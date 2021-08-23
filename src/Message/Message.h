#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>

class Message {
public:
	enum class ACTION : uint8_t { COMMAND, RESPONSE };
    enum class STATUS : uint8_t { 
        DONE, 
        ERROR, //remove!
        BUSY, 
        READY, 
        ACCEPTED 
    };

    friend std::ostream& operator<<(std::ostream& os, const ACTION& action);
    friend std::ostream& operator<<(std::ostream& os, const STATUS& status);
    friend std::ostream& operator<<(std::ostream& os, const Message& msg);

    bool operator==(const Message& msg);

    ACTION action;
    STATUS status;
    int task;
    int sender;

    explicit Message();
    Message(const ACTION _action, const STATUS _status, const int _task, const int _sender);
    Message(const Message& other);
    Message& operator=(Message&& other);
    
    void SetStatus(const STATUS _status)	{ status 	= _status; 	}
    void SetAction(const ACTION _action)	{ action 	= _action; 	}
    void SetTask(const int _task)			{ task 		= _task; 	}

    void GetStatus(const STATUS _status)	{ status 	= _status; 	}
    void GetTask(const int _task)			{ task 		= _task; 	}
    
    void Response(Message::STATUS _status, int _task);
    void Command(Message::STATUS _status, int _task);
};

#endif // MESSAGE_H
