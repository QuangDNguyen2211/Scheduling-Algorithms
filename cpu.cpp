/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <iostream>

#include "cpu.h"

using std::cout;
using std::endl;

// run this task for the specified time slice
void CPU::run(Task *task, int slice) {
    cout << "Running task = [" << task->name << "] [" << task->priority
         << "] [" << task->burst << "] for " << slice << " units." << endl;
}
