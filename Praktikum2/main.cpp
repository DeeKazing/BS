#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include "CPU.h"
#include "Process.h"
#include "SimpleScheduler.h"
#include "RoundRobinScheduler.h"
#include <sstream>

using namespace std;

int main() {
    CPU cpu(new RoundRobinScheduler());
    while(true) {
        string input, cmd, parameter;
        cout << "Intel Core Habibi - CPU Terminal>";
        getline(cin, input);
        stringstream ss(input);
        getline(ss, cmd, ' ');
        getline(ss, parameter, '\n');
        if(cmd == "S" || cmd == "Step") {
            if(parameter.size() <= 0) {
                parameter = "1";
            }
            cpu.simulation(stoi(parameter));
        } else if(cmd == "U" || cmd == "Unblock") {
            cpu.unblockProcess();
        } else if(cmd == "P" || cmd == "Print") {
            cpu.printInformation();
        } else if(cmd == "Q" || cmd == "Quit") {
            cout << "Average cycles per process: " << cpu.getDurchschnittlicheCyclenProProzess() << endl;
            exit(0);
        } else {
            cout << "Unknown cmd!" << endl;
        }
    }
}

