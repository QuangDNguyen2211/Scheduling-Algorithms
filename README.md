# Project 4 - Scheduling Algorithms

These files are a C++ variant of the code that supports the POSIX
implementation of the scheduling algorithms project from *Operating
Systems Concepts, 10th Edition* by Silberschatz, Galvin, and Gagne.

Completing this project will require implementing the `schedule()`
method in  the following C++ files:

* `schedule_fcfs.cpp`
* `schedule_sjf.cpp`
* `schedule_rr.cpp`
* `schedule_priority.cpp`
* `schedule_priority_rr.cpp`

Each scheduler is built as a dynamically loaded "shared object"
(`.so`) file.

The supporting files invoke a scheduling algorithm. The driver program
takes two parameters:

1. The scheduler library to load
2. A text file containing a schedule of tasks

For example, to build and run the FCFS scheduler on `schedule.txt`, enter

```shell-session
$ make driver libschedule_fcfs.so
$ ./driver ./libschedule_fcfs.so schedule.txt
```

The `schedules/` directory contains several sample schedules for testing.
