#include <iostream>
#include <memory>
#include "Server.h"

using namespace std;

int main(int arg, char* args[]) {

    std::unique_ptr<Server> server(new Server());
    
    int listener = server->GetListener();
    int bytes_read;
    
	Message buf[1024];
 
	set<int> clients;
	clients.clear();

	while(true) 
	{
		//заполняем множество сокетов
		fd_set readset;
		FD_ZERO(&readset);
		FD_SET(listener, &readset);

		for(set<int>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			FD_SET(*it, &readset);
		}

		//задаем таймаут
		timeval timeout;
		timeout.tv_sec = 15;
		timeout.tv_usec = 0;

		//Ждем события в одном из сокетов
		int mx = max(listener, *max_element(clients.begin(), clients.end()));
		if(select(mx+1, &readset, NULL, NULL, &timeout) <= 0)
		{
			perror("select");
			exit(3);
		}

		//определяем тип события и выполняем соответствующие действия
		if(FD_ISSET(listener, &readset))
		{
			//поступил новый запрос на соединение, используем accept
			int sock = accept(listener, NULL, NULL);
			if(sock < 0) 
			{
				perror("accept");
				exit(3);
			}

			fcntl(sock, F_SETFL, O_NONBLOCK);
			clients.insert(sock);
		}

		for(set<int>::iterator it = clients.begin(); it != clients.end(); it++)
		{
			if(FD_ISSET(*it, &readset))
			{
				//поступили данные от клиента, читаем их
				bytes_read = recv(*it, buf, 1024, 0);

				if(bytes_read <= 0)
				{
					//соединение прервано, удаляем сокет из множества
					close(*it);
					clients.erase(*it);
					continue;
				}
				
					std::cout << "Received message from client:" << std::endl;
					std::cout << buf[0] << std::endl;
				
				//отправляем данные обрано клиенту
				send(*it, buf, bytes_read, 0);
			}
		}
	}

    return 0;
}
