#include <queue>
#include <memory>
#include <string>
#include "task.h"

class TaskLibrary {
public:
    std::unique_ptr<Task> CreateTask(std::string task_name);
};
