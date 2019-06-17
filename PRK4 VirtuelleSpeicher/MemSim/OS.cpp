#include "OS.h"
#include "HDD.h"
#include "RAM.h"
#include "Process.h"
#include "TableEntry.h"
#include "ReplaceAlgorithm.h"
#include "PageTable.h"
#include "Measurements.h"
#include <iostream>
OS::OS(ReplaceAlgorithm* replaceAlgorithm) : mReplaceAlgorithm(replaceAlgorithm) {
}

OS::~OS() {
}

int OS::handlePageError(int vAddress, Process* process) {
    Measurements::getInstance().pageError();
    int pAddress = -1;
    if((pAddress = load(vAddress, process)) != -1) {
        return pAddress;
    } else {
        return replace(vAddress, process);
    }
}

int OS::load(int vAddress, Process* process) {
    std::cout << "Checking for free frame in memory..." << std::endl;
    int pPageIndex = -1;
    for(int i = 0; i < RAM::getInstance().size(); ++i) {
        if(RAM::getInstance().get(i) == -1) {
            pPageIndex = i/pageSize;
            std::cout << "Free frame found at address " << i << " page " << pPageIndex << std::endl;
            break;
        }
    }
    if(pPageIndex == -1) {
        std::cout << "No free frame" << std::endl;
        return pPageIndex;
    }
    int vPageIndex = (vAddress/pageSize);
    int vPageOffset = (vAddress%pageSize);
    int hddIndex = (process->getPid()*pageSize*pageCount) + (vPageIndex*pageSize);
    for(int i = 0; i < pageSize; ++i) {
        RAM::getInstance().put(HDD::getInstance().get(hddIndex+i), (pPageIndex*pageSize)+i);
    }
    
    TableEntry* lTableEntry = new TableEntry(pPageIndex, process->getPid());
    process->getTable()->operator [](vPageIndex) = lTableEntry;
    
    TableEntry* gTableEntry = new TableEntry(vPageIndex, process->getPid());
    PageTable::getInstance().getPageTable()->operator[](pPageIndex) = gTableEntry;
    
    return (pPageIndex*pageSize)+vPageOffset;
}

int OS::replace(int vAddress, Process* process) {
    std::cout << "Replacing page..." << std::endl;
    return mReplaceAlgorithm->replace(vAddress, process);
}