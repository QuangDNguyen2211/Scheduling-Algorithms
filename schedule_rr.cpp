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
using std::pair;

void ScheduleRR::schedule(CPU *cpu) {
  cout << "ScheduleRR::schedule()" << endl;
  Task *taskToRun;

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
  // Initialize the integer vector to store the value of eack task's waiting time in the list
  vector<int> waitingTime;
  int totalWaitingTime = 0;
  double avgWaitingTime;

  // Initialize the integer vector to store the value of eack task's turnaround time in the list
  vector<int> turnAroundTime;
  int totalTurnAroundTime = 0;
  double avgTurnAroundTime;

  vector<int> responseTime;
  int count = 0;
  int totalResponseTime = 0;
  double avgResponseTime;

  // Before scheduling the tasks in the list, the current time is 0
  int runTime = 0;

  while (!tasks[0]->empty()) {
    taskToRun = pickNextTask();
    if (count < numberOfTasks) {
      // Store the response time of the appropriate task in the list into the vector
      responseTime.push_back(runTime);
      count++;
    }
    if (taskToRun->burst > cpu->QUANTUM) {
      cpu->run(taskToRun, cpu->QUANTUM);
      runTime += cpu->QUANTUM;
    } else {
      cpu->run(taskToRun, taskToRun->burst);
      runTime += taskToRun->burst;
    }
    taskToRun->burst -= cpu->QUANTUM;

    if (taskToRun->burst <= 0) {
      for (int i = 0; i < numberOfTasks; i++) {
        if (taskToRun->name == nameProcess[i]) {
          // Store the waiting time of the appropriate task in the list based on its name into the vector
          waitingTime.push_back(runTime - burstTime[i]);
          // Store the turnaround time of the appropriate task in the list based on its name into the vector
          turnAroundTime.push_back(waitingTime[i] + burstTime[i]);
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
    } else {
      Task *temp = tasks[0]->front();
      tasks[0]->pop_front();
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

Task *ScheduleRR::pickNextTask() {
  return tasks[0]->front();
}

Scheduler *create()
{
    return new ScheduleRR;
}
