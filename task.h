/**
 * Representation of a task in the system.
 */

#ifndef TASK_H
#define TASK_H

#include <string>

using std::string;

// representation of a task
struct Task {
    string name;
    int tid;
    int priority;
    int burst;
};

#endif
