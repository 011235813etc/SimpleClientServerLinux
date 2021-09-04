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



	// std::unique_ptr<TaskList> t_list(new TaskList(argv[1]));
//	(*t_list)[0];
//	(*t_list)[1];

    char path[] = "/home/lemongrab/cpp_projects/vs_code/SimpleClientServerLinux/task_list.txt";

	std::unique_ptr<TaskList> t_list(new TaskList(path));


    // bool isLoader = (argv[2] != "loader");
    // bool isLoader = (std::strcmp(argv[2], "loader") == 0);
    bool isLoader = true;
	ACTION action = (isLoader) ? (ACTION::COMMAND) : (ACTION::RESPONSE);
    // std::unique_ptr<Client> client(new Client(action));
    std::unique_ptr<Client> client;
    if(isLoader) {
        client = std::unique_ptr<Client>(new Client(ACTION::COMMAND, t_list->size()));
    } else {
        client = std::unique_ptr<Client>(new Client(ACTION::RESPONSE));
    }

    if(isLoader) {
      client->LoadTasks();
    } else {
        
    } 
    
    // client->Send();
    // client->Recv(); 
    // client->PrintBuf();

    return 0;
}
