#include "RoundRobinScheduler.h"
#include "Process.h"

RoundRobinScheduler::RoundRobinScheduler() : quantum(2) {
}

Process* RoundRobinScheduler::next(Process* aktuellerProzess) {
    if (aktuellerProzess != NULL) {
        if (aktuellerProzess->getDelta() >= quantum) {
            aktuellerProzess->resetDelta();
            if (readyProcesses.size() > 0) {
                readyProcesses.push_back(aktuellerProzess);
                aktuellerProzess = readyProcesses.front();
                readyProcesses.erase(readyProcesses.begin());
            }
        }
    } else {
        if(readyProcesses.size() > 0) {
            aktuellerProzess = readyProcesses.front();
            readyProcesses.erase(readyProcesses.begin());
        }
    }
    return aktuellerProzess;
}

void RoundRobinScheduler::block(Process* aktuellerProzess) {
    blockedProcesses.push_back(aktuellerProzess);
}

void RoundRobinScheduler::unblock() {
    if(blockedProcesses.size() > 0) {
        Process* toUnblock = blockedProcesses.front();
        blockedProcesses.erase(blockedProcesses.begin());
        readyProcesses.push_back(toUnblock);
    }
}

void RoundRobinScheduler::add(Process* newProcess) {
    readyProcesses.push_back(newProcess);
}