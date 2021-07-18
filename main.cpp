#include <iostream>
#include <memory>
#include "TaskList.h"

enum STATUS : uint8_t {
    DONE,
    ERROR,
    BUSY
};

enum TARGET : uint8_t {
    BROADCAST,
    SINGLE
};

struct pack {
    uint8_t id;
    STATUS status;
    uint8_t task_step;
};

int main(int arg, char* args[]) {

	std::unique_ptr<TaskList> t_list(new TaskList(args[1]));
//	(*t_list)[0];
//	(*t_list)[1];
    return 0;
}
