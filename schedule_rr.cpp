#include <iostream>
#include <tuple>

#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void ScheduleRR::schedule(CPU *cpu) {
  cout << "ScheduleRR::schedule()" << endl;
  Task *task;

  // Initialize the number of tasks in the list and assign to 'numberOfTasks'
  int numberOfTasks = tasks[0]->size();
  // Run all tasks based on the value of a quantum which is 10
  for (int i = 0; i < numberOfTasks; i++) {
    for (int j = 0; j < numberOfTasks; j++) {
      // Get the selected task and prepare to run
      task = pickNextTask();
      // If the value of a specific task's burst is equal or greater than the value of a quantum
      // Then that task will run fully 1 quantum which is 10
      if (task->burst >= cpu->QUANTUM) {
        cpu->run(task, cpu->QUANTUM);
        task->burst -= cpu->QUANTUM;
      } else { // If not, then that task will run based on the value of its burst
        // That task will run exactly from the leftover value of its burst
        if (task->burst > 0) {
          cpu->run(task, task->burst);
          task->burst = 0;
        } else { // If the value of its burst is 0, which means that task is completed,
                 // then it will not run anymore
          continue;
        }
      }
    }
  }
}

Task *ScheduleRR::pickNextTask() {
  // Get the first task of 'sortedPriorityTasks' and assign to 'task'
  Task *task = tasks[0]->front();
  // Remove that task
  tasks[0]->pop_front();
  // Put it into the back of the list
  tasks[0]->push_back(task);
  return task;
}

Scheduler *create(){
  return new ScheduleRR;
}
