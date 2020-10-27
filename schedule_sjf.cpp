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

  // Initialize the vector of int to store all values of tasks' burst
  vector<int> shortestBurst;

  // Initialize the number of tasks' burst in the list
  int numberOfBursts;

  // Store the values of tasks' burst
  for (auto it = tasks[0]->begin(); it != tasks[0]->end(); it++) {
    shortestBurst.push_back((*it)->burst);
    numberOfBursts = shortestBurst.size();
    // If there is a similar value to other values in the vector, then remove it
    for (int i = 0; i < numberOfBursts - 1; i++) {
      if (shortestBurst.back() == shortestBurst[i]) {
        shortestBurst.pop_back();
        // Update the value of 'numberOfBursts' after removing the last element in the vector
        numberOfBursts = shortestBurst.size();
      }
    }
  }

  // Call function sort() to rearrange the values in the vector in the ascending order
  sort(shortestBurst.begin(), shortestBurst.begin() + shortestBurst.size());

  // Put the tasks into a list based on the ascending order of their burst
  for (int i = 0; i < numberOfBursts; i++) {
    for (auto it = tasks[0]->begin(); it != tasks[0]->end(); it++) {
      if ((*it)->burst == shortestBurst[i]) {
        sortedShortestTasks.push_back(*it);
      }
    }
  }

  // Initialize the number of tasks in the list and assign to 'numberOfTasks'
  int numberOfTasks = sortedShortestTasks.size();

  // Run and show the tasks
  for (auto i = 0; i < numberOfTasks; i++) {
    Task *task = pickNextTask();
    cpu->run(task, task->burst);
  }
}

Task *ScheduleSJF::pickNextTask() {
  // Get the first task of 'sortedPriorityTasks' and assign to 'task'
  Task* task = sortedShortestTasks.front();
  // Remove that task
  sortedShortestTasks.pop_front();
  return task;
}

Scheduler *create() {
  return new ScheduleSJF;
}
