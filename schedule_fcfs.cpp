#include <iostream>
#include <tuple>
#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void ScheduleFCFS::schedule(CPU *cpu) {
  Task *task;
  cout << "ScheduleFCFS::schedule()" << endl;
  // Run tasks from the list as FCFS format
  for (auto it = tasks[0]->begin(); it != tasks[0]->end(); it++) {
    task = *it;
    //task = pickNextTask();
    cpu->run(task, task->burst);
  }
}

Task *ScheduleFCFS::pickNextTask() {
  Task *task = tasks[0]->back();
  //tasks[0]->splice(tasks[0]->end(), *tasks[0], tasks[0]->begin());
  return task;
}

Scheduler *create() {
  return new ScheduleFCFS;
}
