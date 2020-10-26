#include <iostream>
#include <tuple>

#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void ScheduleRR::schedule(CPU *cpu)
{
    cout << "ScheduleRR::schedule()" << endl;
    ignore = cpu;
}

Task *ScheduleRR::pickNextTask()
{
    return NULL;
}

Scheduler *create()
{
    return new ScheduleRR;
}
