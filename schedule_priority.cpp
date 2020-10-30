#include <iostream>
#include <tuple>

#include "schedulers.h"

using std::cout;
using std::endl;

list<Task *> sortedPriorityTasks;

void SchedulePriority::schedule(CPU *cpu) {
    cout << "SchedulePriority::schedule()" << endl;

    // Run and show tasks from the list
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

Task *SchedulePriority::pickNextTask() {
  int highest_priority = tasks[0]->front()->priority;

  for (list<Task *> *queue : tasks)
      for (Task *task : *queue)
        if(task->priority < highest_priority)
          highest_priority = task->priority;

  for (list<Task *> *queue : tasks)
      for (Task *task : *queue)
        if(task->priority == highest_priority)
          return task;
}

Scheduler *create() {
    return new SchedulePriority;
}
