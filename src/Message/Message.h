/*! \file Message.h
    \brief Message class declaration.
*/
#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <string>

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

    explicit Message(); 
    Message(const ACTION _action, const STATUS _status, const int _task, const int _sender);
    Message(const Message& other);
    //! \brief Class destructor.
    ~Message() = default;
    Message& operator=(Message&& other);
    
    void SetStatus(const STATUS _status);
    void SetAction(const ACTION _action);
    void SetTask(const int _task);

    void Response(Message::STATUS _status, int _task);
    void Command(Message::STATUS _status, int _task);
};

#endif // MESSAGE_H
