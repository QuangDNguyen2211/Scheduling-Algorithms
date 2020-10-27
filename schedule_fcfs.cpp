#include <iostream>
#include <tuple>
#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void ScheduleFCFS::schedule(CPU *cpu) {
  Task *task;
  cout << "ScheduleFCFS::schedule()" << endl;

  int numberOfTasks = tasks[0]->size();
  // Run and show tasks from the list
  for (int i = 0; i < numberOfTasks; i++) {
    task = pickNextTask();
    cpu->run(task, task->burst);
  }
}

Task *ScheduleFCFS::pickNextTask() {
  // Get the first task of 'sortedPriorityTasks' and assign to 'task'
  Task *task = tasks[0]->front();
  // Remove that task
  tasks[0]->pop_front();
  // Put it into the back of the list
  tasks[0]->push_back(task);
  return task;
}

Scheduler *create() {
  return new ScheduleFCFS;
}
