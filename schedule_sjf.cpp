#include <iostream>
#include <tuple>

#include "schedulers.h"

using std::cout;
using std::endl;
using std::ignore;

void ScheduleSJF::schedule(CPU *cpu)
{
    cout << "ScheduleSJF::schedule()" << endl;
    ignore = cpu;
}

Task *ScheduleSJF::pickNextTask()
{
    return NULL;
}

Scheduler *create()
{
    return new ScheduleSJF;
}
