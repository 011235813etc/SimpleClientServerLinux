//! \file Server.h
//! \brief Server class declaration.

#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <unistd.h>
#include <iostream>
#include "../SocketAddress/SocketAddress.h"
#include "../Message/Message.h"
#include <fcntl.h>
#include <algorithm>
#include <set>
#include <stack>
#include "ServerResponse.h"

//! \brief This class describe the server behavior and used for exchange information with clients.
class Server {
    std::unique_ptr<SocketAddress> soc_addr;	//!< Current socket address.
    int listener;								//! Create lisener socket descriptor.
    Message to_client;                          //!< Used for save prepare message.
    
	timeval timeout;							//!< Used for waiting event in socket.
	int task;									//!< Used for save current task number.
	static const int serial_number = 19700101; 	//!< %Server serial number.

	std::unique_ptr<ServerResponse> prepare_response; 	//!< Used for save response message for client.
	std::stack<int> task_stack;			//!< Used for save tasks from client.
	STATUS status;						//!< Current server status.
	
public:
    explicit Server(uint32_t timeout_sec);
    virtual ~Server();
    
    void CreateSocketQueue(std::set<int>& clients, fd_set& readset);
    void WaitEvent(std::set<int>& clients, fd_set& readset);
    void AddNewClientsRequests(std::set<int>& clients, fd_set& readset);
	void SetTask(uint8_t _task);
	int  GetTask();
	void DataProcessing(Message* from_client, int sock_descriptor);
};

#endif // SERVER_H
