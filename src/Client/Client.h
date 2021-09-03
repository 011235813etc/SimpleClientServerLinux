/*! \file Client.h
    \brief Client class declaration.
*/
#ifndef CLIENT_H
#define CLIENT_H

#include <vector>
#include <memory>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include "../SocketAddress/SocketAddress.h"
#include "../Message/Message.h"
#include "ClientResponse.h"
#include "../TaskList/TaskList.h"
#include "../DebugFlags.h"

class Client {
    std::unique_ptr<SocketAddress> soc_addr;    //!< Current socket address.
    Message to_server;                          //!< Used for save prepare message.
    Message* from_server = nullptr;             //!< Used for point to received message from server.
    int sock_descriptor;                        //!< Used for save socket.
    char buf[sizeof(to_server)];                //!< Buffer for save received information.
    static int serial_number;                   //!< Client serial number.
    std::unique_ptr<ClientResponse> prepare_response;  //!< Used for prepare response message for Server.
public:
    explicit Client(Message::ACTION action=Message::ACTION::COMMAND, unsigned int total_tasks=0);
    virtual ~Client();
    void Send(Message& _to_server);
    void Recv();
    void DataProcessing(Message* from_server);
    int GetSerialNumber();
    void LoadTasks();
    int CommandRequest();

#ifdef DEBUG
  using type_history = std::vector<std::pair<Message, Message::TYPE> >; //!< Typedef for history save vector.
private:
    bool enableHistoryRecording = true;                           //!< Used for enable/disable history recording.
    type_history history;      //!< Used for save sent messages.
public:
    //! \brief Get sent commands history (used only in unit testing).
    //! \return type_history - Sent/received commands history.
    type_history GetHistory() {
        return history;
    }

    //! \brief Get a sign enable history (used only in unit testing).
    //! \return bool - enableHistory status.
    bool IsEnableHistoryRecording() {
        return enableHistoryRecording;
    }

    //! \brief Set a sign enable history (used only in unit testing).
    //! \return void.
    void SetEnableHistoryRecording(bool enable) {
        enableHistoryRecording = enable;
    }
#endif //DEBUG
};

#endif // CLIENT_H
