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
    bool dupPri = false;

    while(!tasks[0]->empty()) {
      Task *taskToRun = pickNextTask();

      for (list<Task *> *queue : tasks)
          for (Task *task : *queue)
            if(task->name != taskToRun->name && task->priority == taskToRun->priority)
              dupPri = true;

      if(taskToRun->burst > cpu->QUANTUM && dupPri == true) {
        cpu->run(taskToRun, cpu->QUANTUM);
        taskToRun->burst -= cpu->QUANTUM;
      }
      else{
        cpu->run(taskToRun, taskToRun->burst);
        taskToRun->burst -= taskToRun->burst;
      }

      if(taskToRun->burst <= 0) {
        for (list<Task *> *queue : tasks)
            for (Task *task : *queue)
              if(task == taskToRun){
                delete task;
              }
        tasks[0]->remove(taskToRun);
        dupPri = false;
      }
      else{
        Task *temp = taskToRun;
        tasks[0]->remove(taskToRun);
        tasks[0]->push_back(temp);
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
