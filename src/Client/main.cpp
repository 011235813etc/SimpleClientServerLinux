/*! \file main.cpp
	\brief Client application entry point.
*/
#include <iostream>
#include <memory>
#include "../TaskList/TaskList.h"
#include "Client.h"

/*! 
    \brief %Client application begin.
    \param int argc -
    \param char* argv[] - 
    \return 0.
*/ 
int main(int argc, char* argv[]) {

//	std::unique_ptr<TaskList> t_list(new TaskList(argv[1]));
//	(*t_list)[0];
//	(*t_list)[1];

	Message::ACTION action = (argv[1] != NULL) ? (Message::ACTION::COMMAND) : (Message::ACTION::RESPONSE);
    std::unique_ptr<Client> client(new Client(action));

    Message message;
    
    if(argv[1] != NULL) {
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
