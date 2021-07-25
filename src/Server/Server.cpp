#include "Server.h"

Server::Server() {

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if(listener < 0) 
	{
		perror("socket");
		exit(1);
	}

	fcntl(listener, F_SETFL, O_NONBLOCK);
	
	
	soc_addr = std::unique_ptr<SocketAddress>(new SocketAddress("127.0.0.1", 3425));
	
	if(bind(listener, (struct sockaddr*)soc_addr->GetPtr(), soc_addr->GetSize()) < 0)
	{
		perror("bind");
		exit(2);
	}

	listen(listener, 2);
}

Server::~Server() {
    close(listener);
}


int Server::GetListener() {
    return listener;
}


