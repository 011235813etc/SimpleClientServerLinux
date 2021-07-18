#include "TaskList.h"


TaskList::TaskList(char* path)
{
    using namespace std;

    auto is_space {
        [](char ch)
        {
            return ch == ' ';
        }
    };

    fstream file(path);
    if(file.is_open())
    {
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
}

TaskList::~TaskList()
{
    //dtor
}

void TaskList::operator[](unsigned int idx) {
    if(idx < commands.size()) {
        if(system(commands[idx].c_str())) {
            std::cout << "Task #" << idx << " - failure!" << std::endl;
        } else {
            std::cout << "Task #" << idx << " - successfull!" << std::endl;
        }
    }
}
