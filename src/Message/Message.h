/*! \file Message.h
    \brief Message class declaration.
*/
#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <string>
#include <climits>

class Message {
public:
    /*! 
        \brief An enum class describe a type of action for client or server.
     */
	enum class ACTION : uint8_t { 
        COMMAND, //!< Command for Client or Server.
        RESPONSE //!< Responce from Client or Server.
    };

    /*!
        \brief An enum class describe status client or server.
     */
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
    Message& operator=(Message&& other);
    
    void SetStatus(const STATUS _status);
    void SetAction(const ACTION _action);
    void SetTask(const int _task);

    void Response(Message::STATUS status, int task);
    void Command(Message::STATUS status, int task);
};

#endif // MESSAGE_H
