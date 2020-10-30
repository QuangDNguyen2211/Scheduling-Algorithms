#include <iostream>
#include <tuple>
#include <list>
#include "schedulers.h"
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;

list<Task *> sortedShortestTasks;

void ScheduleSJF::schedule(CPU *cpu) {
  cout << "ScheduleSJF::schedule()" << endl;

  while(!tasks[0]->empty()) {
    Task *taskToRun = pickNextTask();
    cpu->run(taskToRun, taskToRun->burst);

    for (list<Task *> *queue : tasks)
        for (Task *task : *queue)
          if(task == taskToRun)
            delete task;
    tasks[0]->remove(taskToRun);
  }

}

Task *ScheduleSJF::pickNextTask() {
  int lowest_burst = tasks[0]->front()->burst;

  for (list<Task *> *queue : tasks)
      for (Task *task : *queue)
        if(task->burst < lowest_burst)
          lowest_burst = task->burst;

  for (list<Task *> *queue : tasks)
      for (Task *task : *queue)
        if(task->burst == lowest_burst)
          return task;
}

Scheduler *create() {
  return new ScheduleSJF;
}
