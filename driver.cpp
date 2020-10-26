/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <regex>

#include <dlfcn.h>

#include "task.h"
#include "schedulers.h"
#include "cpu.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::getline;
using std::regex;
using std::sregex_token_iterator;
using std::stoi;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " SCHEDULER SCHEDULE\n" << endl;
        return EXIT_FAILURE;
    }

    void *implementation = dlopen(argv[1], RTLD_LAZY);
    if (implementation == NULL) {
        cerr << dlerror() << endl;
        return EXIT_FAILURE;
    }

    void *pcreate = dlsym(implementation, "create");
    if (pcreate == NULL) {
        cerr << dlerror() << endl;
        return EXIT_FAILURE;
    }
    creator *create = reinterpret_cast<creator *>(pcreate);

    void *pdestroy = dlsym(implementation, "destroy");
    if (pdestroy == NULL) {
        cerr << dlerror() << endl;
        return EXIT_FAILURE;
    }
    destroyer *destroy = reinterpret_cast<destroyer *>(pdestroy);

    Scheduler *scheduler = create();

    ifstream in(argv[2]);
    regex csv_sep("\\s*,\\s*");
    string task;

    while (getline(in, task)) {
        sregex_token_iterator iter(task.begin(), task.end(), csv_sep, -1);

        string name = *iter++;
        int priority = stoi(*iter++);
        int burst = stoi(*iter++);

        // add the task to the scheduler's list of tasks
        scheduler->add(name, priority, burst);
    }

    CPU *cpu = new CPU;

    // invoke the scheduler
    scheduler->schedule(cpu);

    delete cpu;

    destroy(scheduler);

    auto ok = dlclose(implementation);
    if (ok != 0) {
        cerr << dlerror() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
