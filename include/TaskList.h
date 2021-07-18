#ifndef TASKLIST_H
#define TASKLIST_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>

class TaskList
{
    public:
        TaskList(char* path);
        virtual ~TaskList();
        void operator[](unsigned int idx);

    protected:

    private:
    std::vector<std::string> commands;
};

#endif // TASKLIST_H
