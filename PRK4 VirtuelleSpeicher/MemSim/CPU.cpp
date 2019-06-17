/*Die CPU.  Die CPU ist stochastisch, d.h. sie wird von Zufalls-Zahlen gesteuert. 
Sie führt Schritte aus, einen Schritt nach den anderen, 
wobei in einem Schritt eines der folgende Ereignisse passieren wird. 
Jedes Ereignis hat eine fest definierte Wahrscheinlichkeit. 
Die Liste unten ist in der Reihenfolge von wahrscheinlichsten bis unwahrscheinlichsten sortiert:

    Lesen
        ||wie die Adresse für das LOAD-Operation ausgewählt wird, ist nicht definiert, bzw. 
        soll als Teil des jeweiligen Experiments gesehen werden. Anders gesagt, 
        die LOAD- (und STORE-) Operationen verwenden einen austauschbaren Adressengenerator. Sehe unten (!)
        ||Die Daten, die aus dem Speicher gelesen werden, sollen auf Richtigkeit geprüft werden.
        D.h. es soll getestet werden, ob nur der eigenen Seiten gelesen werden. S.o.
    Schreiben -- genau wie Lesen, s.o. -- mutatis mutandis.
    Prozesswechsel -- eigentlich Aufgabe eines Betriebssystems; hier macht die CPU einfach eine willkürliche Prozesswechsel.*/
#include <vector>

#include "CPU.h"
#include "AddressGenerator.h"
#include "Processes.h"
#include "Process.h"
#include "MMU.h"
#include "RAM.h"
#include "Measurements.h"
#include <iostream>

CPU::CPU(AddressGenerator* addressGenerator, MMU* mmu) : mAddressGenerator(addressGenerator), mMMU(mmu) {
}

CPU::~CPU() {
}

void CPU::simulate(int steps) {
    changeProcess();
    for (int i = 0; i < steps; ++i) {
        Measurements::getInstance().tick();
        int random = std::rand() % 7;
        if (random == 0) {
            changeProcess();
        } else if (random > 0 & random < 3) {
            int vAddress = mAddressGenerator->generate();
            store(Processes::getInstance().getCurrentProcess()->getPid(), vAddress);
        } else {
            int vAddress = mAddressGenerator->generate();
            load(vAddress);
        }
    }
}

void CPU::load(int address) {
    std::cout << "LOAD | PID: " << Processes::getInstance().getCurrentProcess()->getPid() << " | vAddress: " << address << std::endl;
    int pAddress = mMMU->translate(address, false);
    std::cout << "pAddress: " << pAddress << std::endl;
    int value = RAM::getInstance().get(pAddress);
    if (value != Processes::getInstance().getCurrentProcess()->getPid()) {
        std::cout << "Error! Process " << Processes::getInstance().getCurrentProcess()->getPid() << " was able to load data from memory belonging to Process " << value << std::endl;
        Measurements::getInstance().unhealthy();
    }
}

void CPU::store(int value, int address) {
    std::cout << "STORE | PID: " << Processes::getInstance().getCurrentProcess()->getPid() << " | vAddress: " << address << std::endl;
    int pAddress = mMMU->translate(address, true);
    std::cout << "pAddress: " << pAddress << std::endl;
    int currentValue = RAM::getInstance().get(pAddress);
    if (currentValue != Processes::getInstance().getCurrentProcess()->getPid()) {
        std::cout << "Error! Process " << Processes::getInstance().getCurrentProcess()->getPid() << " was able to store data at memory belonging to Process " << currentValue << std::endl;
        Measurements::getInstance().unhealthy();
    }
    RAM::getInstance().put(value, pAddress);
}

void CPU::changeProcess() {
    int random = std::rand() % Processes::getInstance().count();
    Processes::getInstance().setCurrentProcess(Processes::getInstance().getProcesses().at(random));
    std::cout << "CHANGE | New PID: " << Processes::getInstance().getCurrentProcess()->getPid() << std::endl;
}

void CPU::printStats() const {
    std::cout << "System is " << (Measurements::getInstance().getHealth() ? "healthy" : "not healthy") << std::endl;
    std::cout << "Total access: " << Measurements::getInstance().getPageAccess() << std::endl;
    std::cout << "Total success: " << Measurements::getInstance().getPageSuccess() << std::endl;
    std::cout << "Total errors: " << Measurements::getInstance().getPageErrors() << std::endl;
    std::cout << "Success ratio: " << Measurements::getInstance().getPageSuccess() / Measurements::getInstance().getPageAccess() << std::endl;
    std::cout << "Error ratio: " << Measurements::getInstance().getPageErrors() / Measurements::getInstance().getPageAccess() << std::endl;
}