#include <iostream>
#include <memory>
#include "../TaskList/TaskList.h"
#include "Client.h"


int main(int arg, char* args[]) {

//	std::unique_ptr<TaskList> t_list(new TaskList(args[1]));
//	(*t_list)[0];
//	(*t_list)[1];

	Message::CLIENT_TYPE ct = (args[1] != NULL) ? (Message::CLIENT_TYPE::MASTER) : (Message::CLIENT_TYPE::COMMON);
    std::unique_ptr<Client> client(new Client(ct));
    
    Message message;
    
    if(args[1] != NULL) {
    	message = Message(Message::STATUS::COMMAND, Message::CLIENT_TYPE::MASTER, Message::TARGET::ALL, 128);
    } else {
    	message = Message(Message::STATUS::READY, Message::CLIENT_TYPE::COMMON, Message::TARGET::OWN, 0);
    } 
    
    client->Send(message);
    client->Recv();
    client->PrintBuf();

    return 0;
}
