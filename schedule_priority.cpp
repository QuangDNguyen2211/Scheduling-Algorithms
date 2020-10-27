#include <iostream>
#include <tuple>

#include "schedulers.h"

using std::cout;
using std::endl;

list<Task *> sortedPriorityTasks;

void SchedulePriority::schedule(CPU *cpu) {
    cout << "SchedulePriority::schedule()" << endl;

    // Sort the tasks based on their priority in the ascending order
    // and store them into 'sortedPriorityTasks'
    for (int i = 1; i <= 10; i++) {
      for (auto it = tasks[0]->begin(); it != tasks[0]->end(); it++) {
        if ((*it)->priority == i) {
          sortedPriorityTasks.push_back(*it);
        }
      }
    }

    int numberOfPriorities = sortedPriorityTasks.size();
    // Run and show the tasks by using SJF Algorithm
    for (auto i = 0; i < numberOfPriorities; i++) {
      Task *task = pickNextTask();
      cpu->run(task, task->burst);
    }
}

Task *SchedulePriority::pickNextTask() {
  // Get the first task of 'sortedPriorityTasks' and assign to 'task'
  Task* task = sortedPriorityTasks.front();
  // Remove that task
  sortedPriorityTasks.pop_front();
  return task;
}

Scheduler *create() {
    return new SchedulePriority;
}
