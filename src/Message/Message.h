/*! \file Message.h
    \brief Message class declaration.
*/
#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <string>
#include <climits>
#include "../DebugFlags.h"



class Message {
public:
#ifdef DEBUG
    //! \brief A sign for save exchange history (Used for unit testsing).
	enum class TYPE : uint8_t { 
        SENT,       //!< Command for Client or Server.
        RECEIVED    //!< Responce from Client or Server.
    };
#endif //DEBUG

    //! \brief An enum class describe a type of action for client or server.
	enum class ACTION : uint8_t { 
        COMMAND, //!< Command for Client or Server.
        RESPONSE //!< Responce from Client or Server.
    };

    //! \brief An enum class describe status client or server.
    enum class STATUS : uint8_t { 
        DONE,       //!< Client or Server are done execute command.
        ERROR,      //!< Client or Server are have error.
        BUSY,       //!< Client or Server are busy.
        READY,      //!< Client or Server are ready for execute command.
        ACCEPTED    //!< Client or Server are accept command or responce.
    };

    friend std::ostream& operator<<(std::ostream& os, const ACTION& action);    
    friend std::ostream& operator<<(std::ostream& os, const STATUS& status);    
    friend std::ostream& operator<<(std::ostream& os, const Message& msg);      

    bool operator==(const Message& msg);  
    friend bool operator==(const Message& m1, const Message& m2);

    ACTION action;  //!< Variable for save current action.
    STATUS status;  //!< Variable for save current status.
    int task;       //!< Variable for save current task. 
    int sender;     //!< Variable for save serial number of sender.
    static const int launch_task = INT_MAX; //!< Variable for launch.
    static const int done_task   = INT_MIN; //!< Variable for stop.

    explicit Message(); 
    Message(const ACTION _action, const STATUS status, const int task, const int sender);
    Message(const Message& other);
    //! \brief Class destructor.
    ~Message() = default;
    Message& operator=(const Message& other);
    
    void SetStatus(const STATUS _status);
    void SetAction(const ACTION _action);
    void SetTask(const int _task);

    void Response(Message::STATUS status, int task);
    void Command(Message::STATUS status, int task);
};

namespace  {
    using ACTION    = Message::ACTION;
    using STATUS    = Message::STATUS;
    using TYPE      = Message::TYPE;
}

#endif // MESSAGE_H
