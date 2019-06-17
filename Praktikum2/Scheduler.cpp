#include "Scheduler.h"

Scheduler::Scheduler() {
    
}

vector<Process*> Scheduler::getAlleBereit() {
    return readyProcesses;
}

vector<Process*> Scheduler::getAllBlocked() {
    return blockedProcesses;
}

