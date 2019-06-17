#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string>

using namespace std;

class Process
{
public:
    Process(int id, int parentId, int prioritaet, int startTime, vector<string> anweisung);
    string getInstruction(int prozessCounter);
    int getId(), getParentId(), getPrioritaet(), getBenutzteCyclen(), getStartTime(), getDelta();
    void addCycle(), resetDelta();
    
private:
    vector<string> anweisung;
    int id, parentId, prioritaet, startTime, cyclenZaehler, cycleDelta;
};