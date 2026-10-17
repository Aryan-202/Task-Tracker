#include <iostream>
#include <string>
#include "Utils.hpp"

using namespace std;

class TaskManager
{
private:
    const std::string& title;
    const std::string& desc;
    int id = Utils::counter(0);
public:
    TaskManager(const std::string& title, const std::string& desc)
        : title(title), desc(desc)
    {
        Utils::createTask(id, title, desc);
    }
};
