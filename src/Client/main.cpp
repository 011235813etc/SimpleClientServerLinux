#include <iostream>
#include <memory>
#include "../TaskList/TaskList.h"
#include "Client.h"


int main(int arg, char* args[]) {

//	std::unique_ptr<TaskList> t_list(new TaskList(args[1]));
//	(*t_list)[0];
//	(*t_list)[1];

	Message::ACTION action = (args[1] != NULL) ? (Message::ACTION::COMMAND) : (Message::ACTION::RESPONSE);
    std::unique_ptr<Client> client(new Client(action));
    
    Message message;
    
    if(args[1] != NULL) {
    	message = Message(Message::ACTION::COMMAND, 
                            Message::STATUS::READY, 
                            128, 
                            client->GetSerialNumber());
    } else {
    	message = Message(Message::ACTION::RESPONSE, 
                            Message::STATUS::BUSY, 
                            0, 
                            client->GetSerialNumber());
    } 
    
    client->Send(message);
    client->Recv();
    // client->PrintBuf();

    return 0;
}
