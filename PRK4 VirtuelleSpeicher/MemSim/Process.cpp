#include "Process.h"

Process::Process(int pid) : mPid(pid) {
    mTable = new std::map<int, TableEntry*>();
}

Process::~Process() {
}

int Process::getPid() const {
    return mPid;
}

std::map<int, TableEntry*>* Process::getTable() {
    return mTable;
}