#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <string>

class Message {
public:
    enum class STATUS       : uint8_t { DONE, ERROR, BUSY, READY, COMMAND, RESPONSE };
    enum class TARGET       : uint8_t { OWN, BY_TURNS, ALL };
    enum class CLIENT_TYPE  : uint8_t { COMMON, MASTER, LOGGER };

    friend std::ostream& operator<<(std::ostream& os, const CLIENT_TYPE& client_type);
    friend std::ostream& operator<<(std::ostream& os, const TARGET& target);
    friend std::ostream& operator<<(std::ostream& os, const STATUS& status);
    friend std::ostream& operator<<(std::ostream& os, const Message& msg);

    STATUS status;
    CLIENT_TYPE client;
    TARGET target;
    uint8_t task_step;

    Message() {
        status = STATUS::READY;
        client = CLIENT_TYPE::COMMON;
        target = TARGET::OWN;
        task_step = 255;
    }
    void Print();
};

#endif // MESSAGE_H
