
#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "Process.h"

class Scheduler {
public:
    Scheduler();
    virtual Process* next(Process* aktuellerProzess) = 0;
    virtual void block(Process* aktuellerProzess) = 0;
    virtual void unblock() = 0;
    virtual void add(Process* newProcess) = 0;
    virtual vector<Process*> getAlleBereit();
    virtual vector<Process*> getAllBlocked();
protected:
    vector<Process*> readyProcesses;
    vector<Process*> blockedProcesses;
};

#endif /* SCHEDULER_H */

