#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <vector>
#include <string>
#include "Process.h"
#include <fstream>
#include <iostream>
#include <map>
#include "Scheduler.h"
using namespace std;
struct prozessDaten {
    int prozessCounter, intRegister;
};

class CPU {
public:
    CPU(Scheduler* aScheduler);
    ~CPU();
    void simulation(int steps), unblockProcess(), printInformation();
    int getDurchschnittlicheCyclenProProzess();

private:
    int prozessCounter, sp, letzteID, time, prozessCyclen, intRegister;
    Process* aktuellerProzess;
    map<int, prozessDaten> processMap;
    Scheduler* scheduler;

    void ausfuehren(string anweisung), setN(int n), addN(int n), subN(int n), blockProcess(), killProcess(), erstelleProzess(string), zeitplan(), save(), restore();
};