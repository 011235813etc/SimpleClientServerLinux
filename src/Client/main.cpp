#include <iostream>
#include <memory>
#include "../TaskList/TaskList.h"
#include "Client.h"


int main(int arg, char* args[]) {

//	std::unique_ptr<TaskList> t_list(new TaskList(args[1]));
//	(*t_list)[0];
//	(*t_list)[1];

//    std::unique_ptr<Client> client(new Client());
//    client->Send();
//    client->Recv();
//    client->PrintBuf();

	std::cout << "I am Client!" << std::endl;

    return 0;
}
