#include <iostream>
#include <tuple>
#include <list>
#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

// Declare 'sortedPriorityTasks' to store tasks
// from the list in ascending order
list<Task *> sortedPriorityTasks;

void ScheduleSJF::schedule(CPU *cpu) {
  cout << "ScheduleSJF::schedule()" << endl;
  // Get the number of tasks in the list and assign to 'numberOfTasks'
  int numberOfTasks = tasks[0]->size();

  // Check the priority of tasks
  // Start from the highest priority
  int check = 1;
  // Sort the tasks in ascending order and store them into 'sortedPriorityTasks'
  for (int i = 0; i < numberOfTasks; i++) {
    for (auto it = tasks[0]->begin(); it != tasks[0]->end(); it++) {
      if ((*it)->priority == check) {
        sortedPriorityTasks.push_back(*it);
      }
    }
    check++;
  }
  // Run and show the tasks by using SJF Algorithm
  for (auto i = 0; i < numberOfTasks; i++) {
    Task *task = pickNextTask();
    cpu->run(task, task->burst);
  }
}

Task *ScheduleSJF::pickNextTask() {
  // Store the first task of 'sortedPriorityTasks' and assign to 'task'
  Task* task = sortedPriorityTasks.front();
  // Remove that task
  sortedPriorityTasks.pop_front();
  // Put it back into 'sortedPriorityTasks'
  sortedPriorityTasks.push_back(task);
  return task;
}

Scheduler *create() {
  return new ScheduleSJF;
}
