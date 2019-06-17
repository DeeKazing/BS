
#include "SimpleScheduler.h"

SimpleScheduler::SimpleScheduler() {
   
}

 Process* SimpleScheduler::next(Process* aktuellerProzess) {
    Process* nextProcess = NULL;
    if(aktuellerProzess == NULL) {
        if(readyProcesses.size() > 0) {
            nextProcess = readyProcesses.front();
            readyProcesses.erase(readyProcesses.begin());
        }
    } else {
        return aktuellerProzess;
    }
    return nextProcess;
}

void SimpleScheduler::block(Process* aktuellerProzess) {
    blockedProcesses.push_back(aktuellerProzess);
}

void SimpleScheduler::unblock() {
    if(blockedProcesses.size() > 0) {
        Process* toUnblock = blockedProcesses.front();
        blockedProcesses.erase(blockedProcesses.begin());
        readyProcesses.push_back(toUnblock);
    }
}

void SimpleScheduler::add(Process* newProcess) {
    readyProcesses.push_back(newProcess);
}