#include <cstdlib>
#include <vector>

#include "Processes.h"
#include "HDD.h"
#include "RAM.h"
#include "PageTable.h"
#include "BubbleSort.h"
#include "RandomWalk.h"
#include "CPU.h"
#include <iostream>
#include "NRU.h"
#include "Clock.h"
#include <random>
#include "time.h"
using namespace std;

int pageSize = 0;
int pageCount = 0;

int main(int argc, char** argv) {
    srand(time(NULL));
    if(argc != 7) {
        std::cout << "Usage: stepCount processCount pageSize pageCount addressAlgo[rw||bs] replaceAlgo[clock||nru]" << std::endl;
        exit(1);
    }
    
    int steps = std::atoi(argv[1]);
    int processCount = std::atoi(argv[2]);
    pageSize = std::atoi(argv[3]);
    pageCount = std::atoi(argv[4]);
    std::string addressAlgo = std::string(argv[5]);
    std::string replaceAlgo = std::string(argv[6]);
    
    AddressGenerator* addressGenerator;
    if(addressAlgo == "bs") {
        addressGenerator = new BubbleSort();
    } else if(addressAlgo == "rw") {
        addressGenerator = new RandomWalk();
    }
    
    ReplaceAlgorithm* replaceAlgorithm;
    if(replaceAlgo == "nru") {
        replaceAlgorithm = new NRU();
    } else if(replaceAlgo == "clock") {
        replaceAlgorithm = new Clock();
    }
    
    HDD::getInstance().init(pageSize*pageCount*processCount);
    RAM::getInstance().init(pageSize*pageCount);
    
    std::vector<Process*> processes;
    for(int i = 0; i < processCount; ++i) {
        processes.push_back(new Process(i));
        for(int k = 0; k < pageCount; ++k) {
            for(int n = 0; n < pageSize; ++n) {
                HDD::getInstance().put(i, (i*pageSize*pageCount)+(k*pageSize)+(n));
            }
        }
    }
    Processes::getInstance().setProcesses(processes);
    OS* os = new OS(replaceAlgorithm);
    MMU* mmu = new MMU(os);
    CPU* cpu = new CPU(addressGenerator, mmu);
    cpu->simulate(steps);
    cpu->printStats();
}

