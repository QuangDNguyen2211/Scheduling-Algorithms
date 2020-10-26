#include <iostream>
#include <tuple>

#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void SchedulePriority::schedule(CPU *cpu)
{
    cout << "SchedulePriority::schedule()" << endl;
    ignore = cpu;
}

Task *SchedulePriority::pickNextTask()
{
    return NULL;
}

Scheduler *create()
{
    return new SchedulePriority;
}
