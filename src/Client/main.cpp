/*! \file main.cpp
	\brief Client application entry point.
*/
#include <iostream>
#include <memory>
#include <cstring> 
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


    // bool isLoader = (argv[2] != "loader");
    bool isLoader = (std::strcmp(argv[2], "loader") == 0);

	Message::ACTION action = (isLoader) ? (Message::ACTION::COMMAND) : (Message::ACTION::RESPONSE);
    std::unique_ptr<Client> client(new Client(action));

    Message message;
    
    if(isLoader) {
        client->Send();
        client->Recv(); 
        //надо тут формировать команды из TaskList.
    } else {
    } 
    
    client->Send();
    client->Recv(); 
    // client->PrintBuf();

    return 0;
}
