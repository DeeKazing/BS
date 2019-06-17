/*Eine MMU (Memory Management Unit).  
Sie soll virtuelle Adressen in physische Adressen übersetzten. Sie verwendet die aktuelle Seitentabelle. 
    ||Falls die Übersetzung nicht möglich ist, soll sie das Betriebssystem auf rufen. S.u. 
    ||Sie sollen selbst festlegen, wie groß die virtuelle Speicherräume sind, 
    d.h. wie viele Bits die Adressen haben, und wie groß eine Seite ist; d.h. 
    wie viele Bits für die Offsets notwendig sind -- 
    und wie viele Bits für die Seitenzahlen übrig bleiben. 
    Es soll relativ leicht sein, diese Konstante auszutauschen, falls wir deren Auswirkungen testen wollen.*/
#include <map>

#include "MMU.h"
#include "OS.h"
#include "Process.h"
#include "TableEntry.h"
#include "Processes.h"
#include "PageTable.h"
#include "Measurements.h"
#include <iostream>
MMU::MMU(OS* os) : mOS(os) {
}

MMU::~MMU() {
}

int MMU::translate(int vAddress, bool modify) {
    int vPageIndex = vAddress / pageSize;
    int vPageOffset = vAddress % pageSize;
    Process* process = Processes::getInstance().getCurrentProcess();
    std::map<int, TableEntry*> &table = *(process->getTable());
    if (table.find(vPageIndex) == table.end()) {
        std::cout << "No entry in table for page " << vPageIndex << std::endl;
        return mOS->handlePageError(vAddress, process);
    } else if (!table.at(vPageIndex)->isPresent()) {
        std::cout << "Entry for page " << vPageIndex << " is marked as not present" << std::endl;
        return mOS->handlePageError(vAddress, process);
    } else {
        Measurements::getInstance().pageSuccess();
        std::cout << "Entry for page " << vPageIndex << " is present" << std::endl;
        int pPageIndex = process->getTable()->at(vPageIndex)->getAddress();
        process->getTable()->at(vPageIndex)->reference();
        PageTable::getInstance().getPageTable()->at(pPageIndex)->reference();
        if (modify) {
            process->getTable()->at(vPageIndex)->modify();
            PageTable::getInstance().getPageTable()->at(pPageIndex)->modify();
        }
        return (pPageIndex*pageSize) + vPageOffset;
    }
}