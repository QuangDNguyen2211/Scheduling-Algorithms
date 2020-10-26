#include <iostream>
#include <tuple>

#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void SchedulePriorityRR::schedule(CPU *cpu)
{
    cout << "SchedulePriorityRR::schedule()" << endl;
    ignore = cpu;
}

Task *SchedulePriorityRR::pickNextTask()
{
    return NULL;
}

Scheduler *create()
{
    return new SchedulePriorityRR;
}
