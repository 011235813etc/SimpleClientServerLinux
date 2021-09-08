//! \file main.cpp
//! \brief Server application entry point.

#include <iostream>
#include <memory>
#include "Server.h"

using namespace std;

//! \brief %Server application begin.
//! \param int argc - arguments count.
//! \param char* argv[1] - timeout for waiting response from client.
//! \return 0.
int main(int argc, char* argv[]) {

	std::cout << "Server is launched" << std::endl << std::endl;

	const uint8_t timeout_sec = (argc == 1) ? 255 : stoi(argv[1]);

    std::unique_ptr<Server> server(new Server(timeout_sec));
    
    int bytes_read;
    
	Message buf[1024];
 
	set<int> clients;
	clients.clear();

	while(true) {
		//fill set with sockets.
		fd_set readset;

		server->CreateSocketQueue(clients, readset);
		server->WaitEvent(clients, readset);
		server->AddNewClientsRequests(clients, readset);

		for(set<int>::iterator it = clients.begin(); it != clients.end(); it++) {
			if(FD_ISSET(*it, &readset)) {
				//read new data from client.
				bytes_read = recv(*it, buf, 1024, 0);

				if(bytes_read <= 0) {
					//connection aborted. delete socket from set.
					close(*it);
					clients.erase(*it);
					continue;
				}
				server->DataProcessing(buf, *it);
			}
		}
	}

    return 0;
}
