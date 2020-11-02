/*
  Team Members: Vinh Tran (Email: kimvinh@csu.fullerton.edu)
								Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)
  Course: CPSC 351 - 04
  Professor: Kenytt Avery
  Project 4: Scheduling Algorithms
*/

#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void SchedulePriorityRR::schedule(CPU *cpu) {
  cout << "SchedulePriorityRR::schedule()" << endl;
  bool dupPri = false;

  const int numberOfTasks = tasks[0]->size();

  // Initialize the integer vector to store the value of each task's burst in the list
  vector<int> burstTime;
  // Initialize the string vector to store the name of eack task in the list
  vector<string> nameProcess;

  // Store the name and burst time of each task in the list into the vector
  for (auto it = tasks[0]->begin(); it != tasks[0]->end(); it++) {
    nameProcess.push_back((*it)->name);
    burstTime.push_back((*it)->burst);
  }

  // Initialize the integer array to store the value of eack task's waiting time in the list
  int waitingTime[numberOfTasks];
  int totalWaitingTime = 0;
  double avgWaitingTime;

  // Initialize the integer array to store the value of eack task's turnaround time in the list
  int turnAroundTime[numberOfTasks];
  int totalTurnAroundTime = 0;
  double avgTurnAroundTime;

  // Initialize the integer vector to store the value of eack task's response time in the list
  vector<int> responseTime;
  // Initialize the string vector to store the name of eack task in the list
  // This vector is to store the name of the task only one time during scheduling
  vector<string> storeTask;
  // Initialize the bool 'notExist' to check if the task is pushed into 'storeTask' more than one
  bool notExist = true;
  int count = 0;
  int totalResponseTime = 0;
  double avgResponseTime;

  // Before scheduling the tasks in the list, the current time is 0
  int runTime = 0;

  while(!tasks[0]->empty()) {
    Task *taskToRun = pickNextTask();
    storeTask.push_back(taskToRun->name);
    for (unsigned int i = 0; i < storeTask.size() - 1; i++) {
      // If the task is already existed in the vector, then not allow to push another time
      if (storeTask.back() == storeTask[i]) {
        storeTask.pop_back();
        notExist = false;
        break;
      } else { // Else, allow to push it into the vector
        notExist = true;
      }
    }

    if (count < numberOfTasks && notExist) {
      // Store the response time of the appropriate task in the list into the vector
      responseTime.push_back(runTime);
    }

    for (list<Task *> *queue : tasks) {
      for (Task *task : *queue) {
        if (task->name != taskToRun->name && task->priority == taskToRun->priority) {
          dupPri = true;
        }
      }
    }

    if (taskToRun->burst > cpu->QUANTUM && dupPri == true) {
      cpu->run(taskToRun, cpu->QUANTUM);
      runTime += cpu->QUANTUM;
      taskToRun->burst -= cpu->QUANTUM;
    } else {
      cpu->run(taskToRun, taskToRun->burst);
      runTime += taskToRun->burst;
      taskToRun->burst -= taskToRun->burst;
    }

    if (taskToRun->burst <= 0) {
      for (int i = 0; i < numberOfTasks; i++) {
        if (taskToRun->name == nameProcess[i]) {
          // Store the waiting time of the appropriate task in the list based on its name into the array
          waitingTime[i] = runTime - burstTime[i];
          // Store the turnaround time of the appropriate task in the list based on its name into the array
          turnAroundTime[i] = waitingTime[i] + burstTime[i];
        }
      }

      for (list<Task *> *queue : tasks) {
        for (Task *task : *queue) {
          if (task == taskToRun) {
              delete task;
          }
        }
      }
      tasks[0]->remove(taskToRun);
      dupPri = false;
    } else {
      Task *temp = taskToRun;
      tasks[0]->remove(taskToRun);
      tasks[0]->push_back(temp);
    }
  }

  for (int i = 0; i < numberOfTasks; i++) {
    // Calculate the total of waiting times of all tasks in the list
    totalWaitingTime += waitingTime[i];
    // Calculate the total of turnaround times of all tasks in the list
    totalTurnAroundTime += turnAroundTime[i];
    // Calculate the total of response times of all tasks in the list
    totalResponseTime += responseTime[i];
  }

  // Calculate the average waiting time
  avgWaitingTime = (double) totalWaitingTime / (double) numberOfTasks;
  // Calculate the average turnaround time
  avgTurnAroundTime = (double) totalTurnAroundTime / (double) numberOfTasks;
  // Calculate the average response time
  avgResponseTime = (double) totalResponseTime / (double) numberOfTasks;
  // Display the average values on the screen
  cout << "Average Waiting Time = " << avgWaitingTime << endl;
  cout << "Average Turnaround Time = " << avgTurnAroundTime << endl;
  cout << "Average Response Time = " << avgResponseTime << endl;
}

Task *SchedulePriorityRR::pickNextTask() {
  int highest_priority = tasks[0]->front()->priority;

  Task *taskToReturn;

  // Find the highest priority from tasks in the list
  for (list<Task *> *queue : tasks) {
    for (Task *task : *queue) {
      if (task->priority < highest_priority) {
        highest_priority = task->priority;
      }
    }
  }

  // Get the highest priority task in the list
  for (list<Task *> *queue : tasks) {
    for (Task *task : *queue) {
      if (task->priority == highest_priority) {
        taskToReturn = task;
        break;
      }
    }
  }
  return taskToReturn;
}

Scheduler *create() {
  return new SchedulePriorityRR;
}
