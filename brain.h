#include <string>
#include <queue>

class Task;
class Brain {
public:
    Brain();
    void AddTask(std::string task_name);
    void StopTask();

    void Excute();

private:
    std::queue<Task*> task_queue_;
};
