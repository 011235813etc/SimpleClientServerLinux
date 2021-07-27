#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>

class Message {
public:
    enum class STATUS       : uint8_t { DONE, ERROR, BUSY, READY, COMMAND, RESPONSE };
    enum class CLIENT_TYPE  : uint8_t { COMMON, MASTER, LOGGER };
    enum class TARGET       : uint8_t { OWN, BY_TURNS, ALL };

    friend std::ostream& operator<<(std::ostream& os, const CLIENT_TYPE& client_type);
    friend std::ostream& operator<<(std::ostream& os, const TARGET& target);
    friend std::ostream& operator<<(std::ostream& os, const STATUS& status);
    friend std::ostream& operator<<(std::ostream& os, const Message& msg);

    STATUS status;
    CLIENT_TYPE client;
    TARGET target;
    uint8_t task;

    Message() {
        status = STATUS::READY;
        client = CLIENT_TYPE::COMMON;
        target = TARGET::OWN;
        task = 0;
    }
    
    Message(STATUS _status, CLIENT_TYPE _client, TARGET _target, int _task) {
        status 	= _status;
        client 	= _client;
        target 	= _target;
        task 	= _task;
    }
    
    void SetStatus(STATUS _status) 		{ status 	= _status; 	}
    void SetClient(CLIENT_TYPE _client) { client 	= _client; 	}
    void SetTarget(TARGET _target) 		{ target 	= _target; 	}
    void SetTask(int _task) 			{ task 		= _task; 	}
};

#endif // MESSAGE_H
