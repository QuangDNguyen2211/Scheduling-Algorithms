#include <iostream>
#include <tuple>

#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void ScheduleRR::schedule(CPU *cpu) {
  cout << "ScheduleRR::schedule()" << endl;
  Task *taskToRun;

  while(!tasks[0]->empty()) {
    taskToRun = pickNextTask();
    if(taskToRun->burst > cpu->QUANTUM)
      cpu->run(taskToRun, cpu->QUANTUM);
    else
      cpu->run(taskToRun, taskToRun->burst);

    taskToRun->burst -= cpu->QUANTUM;

    if(taskToRun->burst <= 0) {
      for (list<Task *> *queue : tasks)
          for (Task *task : *queue)
            if(task == taskToRun){
              delete task;
            }
      tasks[0]->remove(taskToRun);
    }
    else{
      Task *temp = tasks[0]->front();
      tasks[0]->pop_front();
      tasks[0]->push_back(temp);
    }
  }
}

Task *ScheduleRR::pickNextTask() {
  return tasks[0]->front();
}

Scheduler *create()
{
    return new ScheduleRR;
}
