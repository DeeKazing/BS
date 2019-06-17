#include <vector>
#include <map>

#include "NRU.h"
#include "PageTable.h"
#include "TableEntry.h"
#include "HDD.h"
#include "RAM.h"
#include "Processes.h"
#include "Process.h"

NRU::NRU() {
}

NRU::~NRU() {
}

int NRU::replace(int vAddress, Process* process) {
    std::vector<int> classZero;
    std::vector<int> classOne;
    std::vector<int> classTwo;
    std::vector<int> classThree;
    TableEntry* tableEntry;
    for (int i = 0; i < pageCount; ++i) {
        tableEntry = PageTable::getInstance().getPageTable()->at(i);
        if (!tableEntry->wasReferenced() && !tableEntry->wasModified()) {
            classZero.push_back(i);
        } else if (tableEntry->wasReferenced() && tableEntry->wasModified()) {
            classThree.push_back(i);
        } else if (tableEntry->wasModified()) {
            classOne.push_back(i);
        } else if (tableEntry->wasReferenced()) {
            classTwo.push_back(i);
        }
    }
    int pPageIndex;
    if (classZero.size() > 0) {
        int random = std::rand() % classZero.size();
        pPageIndex = classZero.at(random);
    } else if (classOne.size() > 0) {
        int random = std::rand() % classOne.size();
        pPageIndex = classOne.at(random);
    } else if (classTwo.size() > 0) {
        int random = std::rand() % classTwo.size();
        pPageIndex = classTwo.at(random);
    } else if (classThree.size() > 0) {
        int random = std::rand() % classThree.size();
        pPageIndex = classThree.at(random);
    }
    tableEntry = PageTable::getInstance().getPageTable()->at(pPageIndex);
    Process* ownerProcess = Processes::getInstance().getProcess(tableEntry->getOwner());
    int vPageIndexCurrent = tableEntry->getAddress();
    int vPageIndexNew = (vAddress / pageSize);
    ownerProcess->getTable()->at(tableEntry->getAddress())->setPresent(false);

    for (int i = 0; i < pageSize; ++i) {
        if (tableEntry->wasModified()) {
            HDD::getInstance().put(RAM::getInstance().get((pPageIndex * pageSize) + i), (ownerProcess->getPid() * pageSize * pageCount)+(vPageIndexCurrent * pageSize) + i);
        }
        RAM::getInstance().put(HDD::getInstance().get((process->getPid() * pageSize * pageCount)+(vPageIndexNew * pageSize) + i), (pPageIndex * pageSize) + i);
    }
    delete tableEntry;
    PageTable::getInstance().getPageTable()->operator[](pPageIndex) = new TableEntry(vPageIndexNew, process->getPid());
    if (process->getTable()->find(vPageIndexNew) != process->getTable()->end()) {
        delete process->getTable()->at(vPageIndexNew);
    }
    process->getTable()->operator[](vPageIndexNew) = new TableEntry(pPageIndex, process->getPid());
    return (pPageIndex * pageSize)+(vAddress % pageSize);
}
