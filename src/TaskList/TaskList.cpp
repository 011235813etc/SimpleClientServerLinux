//! \file TaskList.cpp
//! \brief TaskList class implementation.
//! 
//! Used for save commands from file and get them from index.

#include "TaskList.h"

//! \brief Constructor with argument.
//! 
//! Creates a list of task and save him to std::vector.
//! Comments like "//" will be ignored.
//! 
//! \param char* path - path to the file with commands.
//! \return void.
TaskList::TaskList(char* path) {
    using namespace std;

    auto is_space {
        [](char ch) {
            return ch == ' ';
        }
    };

    cout << path << endl;

    fstream file(path);
    if(file.is_open()) {
        const string script_def = ".sh";
        const string comment_def = "//";

        string line;
        while(getline(file, line)) {
            line.erase(remove_if(line.begin(),line.end(), is_space),line.end());

            auto pos = line.find(comment_def);
            if(pos != string::npos) {
                 line.erase(pos);
            }

            if(line.find(script_def) == line.size() - 3) {
                cout << "line:" << line << endl;
                commands.push_back(line);
            }
        }
    }
    file.close();
}

//! \brief Get command from vector by index.
//! \param unsigned int idx - command index.
//! \return bool - execution result.
bool TaskList::operator[](unsigned int idx) {
    bool result = false;
    if(idx < commands.size()) {
        
        if(system(commands[idx].c_str())) {
            std::cout << "Task #" << idx << " - failure!" << std::endl;
            result = false;
        } else {
            std::cout << "Task #" << idx << " - successfull!" << std::endl;
            result = true;
        }
        // using namespace std::chrono;

        // milliseconds ms = duration_cast< milliseconds >( 
        //     system_clock::now().time_since_epoch()
        // );
        // std::cout << "It took me " << ms.count() << " milliseconds.\n\n";
    }
    return result;
}

//! \brief Get command count.
//! \return size_t - command count
size_t TaskList::size() {
    return commands.size();
}