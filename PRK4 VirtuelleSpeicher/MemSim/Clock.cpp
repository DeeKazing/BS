#include <map>
#include <vector>

#include "Clock.h"
#include "PageTable.h"
#include "TableEntry.h"
#include "Processes.h"
#include "Process.h"
#include "HDD.h"
#include "RAM.h"

Clock::Clock() : ReplaceAlgorithm(), mHead(0) {
}

Clock::~Clock() {
}

int Clock::replace(int vAddress, Process* process) {
    int vPageIndex = (vAddress / pageSize);
    int vPageOffset = (vAddress % pageSize);
    bool terminate = false;
    int pPageIndex;
    TableEntry* headEntry;
    while (!terminate) {
        headEntry = PageTable::getInstance().getPageTable()->at(mHead);
        if (headEntry->wasReferenced()) {
            headEntry->setReferenced(false);
        } else {
            pPageIndex = mHead;
            terminate = true;
        }
        mHead = (mHead + 1) % pageCount;
    }

    Process* ownerProcess = Processes::getInstance().getProcess(PageTable::getInstance().getPageTable()->at(pPageIndex)->getOwner());
    ownerProcess->getTable()->at(headEntry->getAddress())->setPresent(false);
    for (int i = 0; i < pageSize; ++i) {
        if (headEntry->wasModified()) {
            HDD::getInstance().put(RAM::getInstance().get(pPageIndex * pageSize + i), (ownerProcess->getPid() * pageSize * pageCount)+(headEntry->getAddress() * pageSize) + i);
        }
        RAM::getInstance().put(HDD::getInstance().get((process->getPid() * pageSize * pageCount)+(vPageIndex * pageSize) + i), (pPageIndex * pageSize) + i);
    }
    delete headEntry;
    PageTable::getInstance().getPageTable()->operator[](pPageIndex) = new TableEntry(vPageIndex, process->getPid());
    if (process->getTable()->find(vPageIndex) != process->getTable()->end()) {
        delete process->getTable()->at(vPageIndex);
    }
    process->getTable()->operator[](vPageIndex) = new TableEntry(pPageIndex, process->getPid());
    return (pPageIndex * pageSize)+vPageOffset;
}

