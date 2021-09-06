/*! \file TaskList.h
    \brief TaskList class declaration.

    Class using for save commands from file and get them from index.
*/

#ifndef TASKLIST_H
#define TASKLIST_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>

class TaskList {

    std::vector<std::string> commands;  //!< Using for save commands from file.
public:
    TaskList(char* path);
    //! \brief Class destructor.
    virtual ~TaskList() = default;
    bool operator[](unsigned int idx);
    size_t size();
};

#endif // TASKLIST_H