#include <iostream>
#include <tuple>

#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void SchedulePriorityRR::schedule(CPU *cpu)
{
    cout << "SchedulePriorityRR::schedule()" << endl;
    int lowest_priority = tasks[0]->front()->priority;
    int i = 1;

    for (list<Task *> *queue : tasks)
        for (Task *task : *queue)
          if(task->priority > lowest_priority)
            lowest_priority = task->priority;

    while(!tasks[0]->empty()) {
      Task *taskToRun = pickNextTask();
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
        if(taskToRun->priority == lowest_priority * i){
          i++;
        }
        taskToRun->priority += lowest_priority * i;
      }
    }
}

Task *SchedulePriorityRR::pickNextTask()
{
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

Scheduler *create()
{
    return new SchedulePriorityRR;
}
