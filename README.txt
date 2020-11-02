This 'README.txt' file is based on 'README.md' from the source: 
https://github.com/ProfAvery/cpsc351/tree/main/project4

# Team Members: 
Vinh Tran (Email: kimvinh@csu.fullerton.edu)
Quang Nguyen (Email: quangdnguyen2211@csu.fullerton.edu)

# Course: CPSC 351 - 04

# Professor: Kenytt Avery

# Project 4 - Scheduling Algorithms

This project is to implement the algorithm for scheduling tasks by using different methods
(e.g. First Come First Serve (FCFS), Shortest Job First (SJF), Priority, Round Robin (RR),
and the combination between Priority and RR).

We also calculate the average values, such as waiting time, turnaround time, and response time
for each method.

**** FCFS Algorithm (Non-Preemptive) ****

We implemented the code to schedule the tasks to run based on the order of tasks added
to the list. Specifically, the first task added to the list will be run first.

**** SJF Algorithm (Non-Preemptive) ****

We designed the code to schedule the tasks to run based on their burst time. That means the task
which has the shortest burst time will be run first.

**** Priority Algorithm (Non-Preemptive) ****

In this project, the priority of each task is ranged from 1 to 10, and the priortity of 1 is
the highest while the priority of 10 is the lowest. Therefore, we implemented the code to
schedule the tasks to run based on their priority. In other words, the task which has the highest
priority will be run first. If there are two or more task that have the same highest priority,
then these tasks will be run by using the FCFS method.

**** Round Robin Algorithm (Preemptive) ****

In this project, A quantum is equal to 10. We implemented the code to schedule the task to run
upto 1 quantum. That means the task can be preempted by another task if it completely runs a quantum.

**** Priority & Round Robin Algorithm (Preemptive) ****

The priority is ranged from 1 and 10, and the quantum is equal to 10.
We implemented the code to schedule the tasks to run based on their priority first. If the task
is the only one which has the highest priority, then it can run completely its burst time before
scheduling another task. If there are two or more tasks that have the same highest priority,
the tasks will be run based on RR by using the quantum.

**** Calculation the average values ****

We used vectors to store the waiting time, turnaround time, and response time of each appropriate task.
In non-preemptive methods, the waiting time of the first task is always 0.

By calculating the waiting time of each task, we use the formula:
Waiting Time of the next task = Burst Time of the previous task + Waiting of the previous task.
Or, in RR and the combination betwen Priority and RR,
Waiting Time of the task = Running Time - Its burst time.

By calculating the turnaround time of each task, we use the formula:
Turnaround Time of the task = the sum of its burst time and waiting time

In non-preemptive methods, the response time of each task is equal to its waiting time.
Otherwise, the response time is the time the task scheduled for first time.

## "CPSC-351-Project4.tar.gz" Contents:

1. README.txt                // this file

2. Makefile                  // instruct how to compile and run the program

3. cpu.cpp                   // implementation of cpu

4. cpu.h                     // header file containing class definition

5. schedulers.cpp            // implementation of scheduler

6. schedulers.h              // header file containing class definition

7. task.h                    // header file containing class definition

8. driver.cpp                // driver program that uses scheduler

9. schedule_fcfs.cpp         // contain the FCFS algorithm and calculations the average values

10. schedule_sjf.cpp         // contain the SJF algorithm and calculations the average values

11. schedule_priority.cpp    // contain the Priority algorithm and calculations the average values

12. schedule_rr.cpp          // contain the RR algorithm and calculations the average values

13. schedule_priority_rr.cpp // contain the Priority & RR algorithm and calculations the average values

14. "schedules" folder       // contain text files to test the program
  14.1. book.txt
  14.2. pri-schedule.txt
  14.3. rr-schedule.txt
  14.4. schedule.txt

## Makefile

To run the make file, command: $ make

Then there are many files created, such as

1. libschedule_fcfs.so
2. libschedule_sjf.so
3. libschedule_priority.so
4. libschedule_rr.so
5. libschedule_priority_rr.so

These files are to use to schedule the tasks by using different methods as stated above.

To run the program quickly, command: $ make test

Or, to run the program, follow the syntax: $ ./driver ./name_of_method.so link_of_test_file
For example, to run the program by using the test file "book.txt" and the FCFS method, command:
$ ./driver ./libschedule_fcfs.so schedules/book.txt

Or, to run the program by using the test file "schedule.txt" and the Priority method, command:
$ ./driver ./libschedule_priority.so schedules/schedule.txt