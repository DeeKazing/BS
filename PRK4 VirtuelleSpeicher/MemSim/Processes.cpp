#include <vector>

#include "Processes.h"

Processes::~Processes() {
}

void Processes::setCurrentProcess(Process* process) {
    mCurrentProcess = process;
}

Process* Processes::getCurrentProcess() {
    return mCurrentProcess;
}

Process* Processes::getProcess(int pid) {
    return mProcesses.at(pid);
}

void Processes::setProcesses(std::vector<Process*> processes) {
    mProcesses = processes;
}

std::vector<Process*> Processes::getProcesses() {
    return mProcesses;
}

int Processes::count() {
    return mProcesses.size();
}

