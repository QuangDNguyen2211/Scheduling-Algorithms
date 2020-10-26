#ifndef SCHEDULERS_H
#define SCHEDULERS_H

#include <string>
#include <vector>
#include <list>

#include "task.h"
#include "cpu.h"

using std::string;
using std::vector;
using std::list;


class Scheduler {
    static const auto MIN_PRIORITY = 1;
    static const auto MAX_PRIORITY = 10;

    public:
        Scheduler();
        virtual ~Scheduler();

        // add a task to the list
        virtual void add(string name, int priority, int burst);

        // invoke the scheduler
        virtual void schedule(CPU *) = 0;

        virtual Task *pickNextTask() = 0;
    protected:
        int next_tid;

        // multi-level queue
        vector<list<Task *> *> tasks;
};

typedef Scheduler* creator();
typedef void destroyer(Scheduler *);

extern "C" {
    Scheduler *create();
    void destroy(Scheduler *);
}

class ScheduleFCFS : public Scheduler {
    public:
        void schedule(CPU *) override;
        Task *pickNextTask() override;
};

class ScheduleSJF : public Scheduler {
    public:
        void schedule(CPU *) override;
        Task *pickNextTask() override;
};

class SchedulePriority : public Scheduler {
    public:
        void schedule(CPU *) override;
        Task *pickNextTask() override;
};

class ScheduleRR : public Scheduler {
    public:
        void schedule(CPU *) override;
        Task *pickNextTask() override;
};

class SchedulePriorityRR : public Scheduler {
    public:
        void schedule(CPU *) override;
        Task *pickNextTask() override;
};

#endif
