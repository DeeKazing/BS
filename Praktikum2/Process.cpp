#include "Process.h"

Process::Process(int id, int parentId, int prioritaet, int startTime, vector<string> anweisung) : id(id), 
        parentId(parentId), prioritaet(prioritaet), startTime(startTime), anweisung(anweisung), cyclenZaehler(0),cycleDelta(0) {
}

int Process::getId() {
    return id;
}

int Process::getParentId() {
    return parentId;
}

int Process::getPrioritaet() {
    return prioritaet;
}

string Process::getInstruction(int prozessCounter) {
        return anweisung[prozessCounter];
}

int Process::getStartTime() {
    return startTime;
}

int Process::getBenutzteCyclen() {
    return cyclenZaehler;
}

void Process::addCycle() {
    ++cyclenZaehler;
    ++cycleDelta;
}

void Process::resetDelta() {
    cycleDelta = 0;
}

int Process::getDelta() {
    return cycleDelta;
}