#include <iostream>

#include "schedulers.h"

using std::cout;
using std::endl;

Scheduler::Scheduler()
{
    next_tid = 1;

    // initially only a single queue
    auto queue = new list<Task *>;
    tasks.push_back(queue);
}

void Scheduler::add(string name, int priority, int burst)
{
    cout << "Scheduler::add(\"" << name << "\", " << priority << ", " << burst << ")" << endl;

    auto task = new Task;
    task->name = name;
    task->tid = next_tid++;
    task->priority = priority;
    task->burst = burst;

    // add to first queue
    tasks[0]->push_back(task);
}

Scheduler::~Scheduler()
{
    for (list<Task *> *queue : tasks) {
        for (Task *task : *queue) {
            delete task;
        }
        delete queue;
    }
}

extern "C" void destroy(Scheduler *scheduler)
{
    delete scheduler;
}
