#include "CPU.h"
#include "Scheduler.h"
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <cstring>

CPU::CPU(Scheduler* aScheduler) : aktuellerProzess(NULL), scheduler(aScheduler), prozessCounter(0), sp(0), prozessCyclen(0), time(0), letzteID(0), intRegister(0) {
    erstelleProzess("init");
    aktuellerProzess = scheduler->next(aktuellerProzess);
}

CPU::~CPU() {
    delete scheduler;
}

void CPU::simulation(int steps) {
    for (int i = 0; i < steps; ++i) {
        if (aktuellerProzess != NULL) {
            string anweisung = aktuellerProzess->getInstruction(prozessCounter++);
            aktuellerProzess->addCycle();
            ausfuehren(anweisung);
            ++prozessCyclen;
        }
        save();
        aktuellerProzess = scheduler->next(aktuellerProzess);
        restore();
        ++time;
    }
}

void CPU::ausfuehren(string anweisung) {
    string cmd;
    string parameter;
    stringstream instructionStream(anweisung);
    getline(instructionStream, cmd, ' ');
    getline(instructionStream, parameter, ' ');
/*switch(cmd){
	case 'S': setN(stoi(parameter));
	case 'A': addN(stoi(parameter));
	case 'D': subN(stoi(parameter));
	case 'B': blockProcess(); zeitplan();
	case 'E': killProcess(); zeitplan();
	case 'R': erstelleProzess(parameter); zeitplan();
}
*/
  if (cmd == "S") {
        setN(stoi(parameter));
    } else if (cmd == "A") {
        addN(stoi(parameter));
    } else if (cmd == "D") {
        subN(stoi(parameter));
    } else if (cmd == "B") {
        blockProcess();
        zeitplan();
    } else if (cmd == "E") {
        killProcess();
        zeitplan();
    } else if (cmd == "R") {
        erstelleProzess(parameter);
        zeitplan();
    }

}

void CPU::setN(int n) {
    intRegister = n;
}
void CPU::addN(int n) {
    intRegister += n;
}
void CPU::subN(int n) {
    intRegister -= n;
}
void CPU::blockProcess() {
    save();
    scheduler->block(aktuellerProzess);
    aktuellerProzess = NULL;
}
void CPU::unblockProcess() {
    scheduler->unblock();
}
void CPU::killProcess() {
    cout << aktuellerProzess->getId() << " terminated" << endl;
    delete aktuellerProzess;
    aktuellerProzess = NULL;
}
void CPU::erstelleProzess(string filename) {
    ifstream file;
    file.open(filename);
    vector<string> anweisungen;
    while (true) {
        string anweisung;
        getline(file, anweisung);
        anweisungen.push_back(anweisung);
        if (file.eof()) {
            break;
        }
    }
    Process* process = new Process(letzteID, (aktuellerProzess == NULL ? 0 : aktuellerProzess->getId()), 0, time, anweisungen);
    scheduler->add(process);
    prozessDaten speichern;
    speichern.intRegister = 0;
    speichern.prozessCounter = 0;
    processMap[process->getId()] = speichern;
    ++letzteID;
}

void CPU::printInformation() {
    cout << "****************************************************************" << endl;
    cout << "The current system state is as follows" << endl;
    cout << "****************************************************************" << endl;
    cout << "CURRENT TIME: " << time << endl;
    cout << "RUNNING PROCESS:" << endl;
    cout << left << setw(10) << "pid" << setw(10) << "ppid" << setw(10) << "prioritaet" << setw(10) << "value" << setw(15) << "start time" << setw(25) << "CPU time used so far" << endl;
    if (aktuellerProzess != NULL) {
        cout << left << setw(10) << aktuellerProzess->getId() << setw(10) << aktuellerProzess->getParentId() << setw(10) << aktuellerProzess->getPrioritaet() << setw(10) << intRegister << setw(15) << aktuellerProzess->getStartTime() << setw(25) << aktuellerProzess->getBenutzteCyclen() << endl;
    }
    cout << "BLOCKED PROCESSES:" << endl;
    cout << left << setw(10) << "pid" << setw(10) << "ppid" << setw(10) << "prioritaet" << setw(10) << "value" << setw(15) << "start time" << setw(25) << "CPU time used so far" << endl;
    vector<Process*> blockedProcesses = scheduler->getAllBlocked();
    for (Process* process : blockedProcesses) {
        cout << left << setw(10) << process->getId() << setw(10) << process->getParentId() << setw(10) << process->getPrioritaet() << setw(10) << processMap.at(process->getId()).intRegister << setw(15) << process->getStartTime() << setw(25) << process->getBenutzteCyclen() << endl;
    }
    cout << "PROCESSES READY TO ausfuehren:" << endl;
    cout << left << setw(10) << "pid" << setw(10) << "ppid" << setw(10) << "prioritaet" << setw(10) << "value" << setw(15) << "start time" << setw(25) << "CPU time used so far" << endl;
    vector<Process*> readyProcesses = scheduler->getAlleBereit();
    for (Process* process : readyProcesses) {
        cout << left << setw(10) << process->getId() << setw(10) << process->getParentId() << setw(10) << process->getPrioritaet() << setw(10) << processMap.at(process->getId()).intRegister << setw(15) << process->getStartTime() << setw(25) << process->getBenutzteCyclen() << endl;
    }
}

void CPU::zeitplan() {
    save();
    aktuellerProzess = scheduler->next(aktuellerProzess);
    restore();
}

void CPU::save() {
    if (aktuellerProzess != NULL) {
        prozessDaten speichern;
        speichern.intRegister = intRegister;
        speichern.prozessCounter = prozessCounter;
        processMap[aktuellerProzess->getId()] = speichern;
    }
}

void CPU::restore() {
    if (aktuellerProzess != NULL) {
        intRegister = processMap.at(aktuellerProzess->getId()).intRegister;
        prozessCounter = processMap.at(aktuellerProzess->getId()).prozessCounter;
    }
}

int CPU::getDurchschnittlicheCyclenProProzess() {
    return prozessCyclen / letzteID;
}
