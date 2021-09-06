/*! \file main.cpp
	\brief Client application entry point.
*/
#include <iostream>
#include <memory>
#include <cstring> 
#include "../TaskList/TaskList.h"
#include "Client.h"

#include <string.h>

#include <chrono>
#include <thread>

/*! 
    \brief %Client application begin.
    \param int argc -
    \param char* argv[] - 
    \return 0.
*/ 
int main(int argc, char* argv[]) {
    
    using namespace std;

    if(argc == 1) {
        cout << "Do not find path to the file with tasks list!" << endl << endl;
        return 0;
    }

    //**//
    // argv[1] = "/home/lemongrab/cpp_projects/vs_code/SimpleClientServerLinux/tasks/task_list.txt";
    // argv[2] = "loader";
    // argc = 3;
    //**//

	unique_ptr<TaskList> t_list(new TaskList(argv[1]));

    //**//
    // char* path_test_server2 = "./../../tasks/launch_server.sh";
    // system(path_test_server2);

    // const uint8_t one_sec = 1;
    // chrono::seconds dura(one_sec);
    // this_thread::sleep_for(dura);
    //**//

    bool isLoader = false;
    if(argc == 3) {
        if (strcmp(argv[2],"loader") == 0) {
            isLoader = true;
        } else {
            cout << "Unknown command." << endl;
            return 0;
        }
    } else {
        isLoader = false;
    }

    unique_ptr<Client> client;
    if(isLoader) {
        client = unique_ptr<Client>(new Client(ACTION::COMMAND, t_list->size()));
    } else {
        client = unique_ptr<Client>(new Client());
    }

    if(isLoader) {
        client->LoadTasks();
    }

    int executed_tasks_count = 0;
    int task_number = 0;
    while(task_number > -1) {
        task_number = client->CommandRequest();
        if(task_number > -1) {
            (*t_list)[task_number];

            executed_tasks_count++;
        }
    }
    cout << endl << executed_tasks_count << " out of "  << t_list->size() << " tasks was executed.";

    return 0;
}
