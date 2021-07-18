#include <iostream>
#include <memory>
#include "TaskList.h"

enum STATUS : uint8_t {
    DONE,
    ERROR,
    BUSY,
    READY,
    COMMAND,
    RESPONSE
};

enum TARGET : uint8_t {
    OWN,
    BY_TURNS,
    ALL
};

enum TYPE : uint8_t {
    LOGGER,
    MASTER,
    NORMAL
};

struct command {
    STATUS status;
    TYPE client_type;
    TARGET target;
    uint8_t task_step;
};

int main(int arg, char* args[]) {

	std::unique_ptr<TaskList> t_list(new TaskList(args[1]));
//	(*t_list)[0];
//	(*t_list)[1];
    return 0;
}
