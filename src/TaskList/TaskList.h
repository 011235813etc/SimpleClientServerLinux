//! \file TaskList.h
//! \brief TaskList class declaration.

#ifndef TASKLIST_H
#define TASKLIST_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <iostream>

#include <chrono>

//! \brief This class used for save commands from file and get them from index.
class TaskList {

    std::vector<std::string> commands;  //!< Used for save commands from file.
public:
    TaskList(char* path);
    //! \brief Class destructor.
    virtual ~TaskList() = default;
    bool operator[](unsigned int idx);
    size_t size();
};

#endif // TASKLIST_H