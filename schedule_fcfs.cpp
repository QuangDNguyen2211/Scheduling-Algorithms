#include <iostream>
#include <tuple>
#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void ScheduleFCFS::schedule(CPU *cpu) {
  cout << "ScheduleFCFS::schedule()" << endl;

  // Run and show tasks from the list
  while(!tasks[0]->empty()) {
    Task *taskToRun = pickNextTask();
    cpu->run(taskToRun, taskToRun->burst);
    for (list<Task *> *queue : tasks) {
        for (Task *task : *queue) {
          if(task == taskToRun)
            delete task;
        }
    }
    tasks[0]->pop_front();
  }
}

Task *ScheduleFCFS::pickNextTask() {
  return tasks[0]->front();
}

Scheduler *create() {
  return new ScheduleFCFS;
}
