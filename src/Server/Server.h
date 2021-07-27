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

class Server {
    std::unique_ptr<SocketAddress> soc_addr;
    int listener;
    
	//задаем таймаут
	timeval timeout;
	int task;

public:
    explicit Server(uint32_t timeout_sec);
    virtual ~Server();
    
    void CreateSocketQueue(std::set<int>& clients, fd_set& readset);
    void WaitEvent(std::set<int>& clients, fd_set& readset);
    void AddNewClientsRequests(std::set<int>& clients, fd_set& readset);
	void SetTask(uint8_t _task) { task = _task;	}
	uint8_t GetTask()			{ return task;	}
};

#endif // SERVER_H
