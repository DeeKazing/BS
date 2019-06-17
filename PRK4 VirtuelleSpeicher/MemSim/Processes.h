#ifndef PROCESSES_H
#define PROCESSES_H
#include "Process.h"
extern int pageSize;
extern int pageCount;

class Processes {
public:
    static Processes& getInstance() {
        static Processes instance;
        return instance;
    }
    Processes(const Processes& orig) = delete;
    void operator=(Processes const&) = delete;
    virtual ~Processes();
    
    
    void setProcesses(std::vector<Process*> processes);
    void setCurrentProcess(Process* process);
    std::vector<Process*> getProcesses();
    Process* getCurrentProcess();
    Process* getProcess(int pid);
    int count();
private:
    Process* mCurrentProcess;
    std::vector<Process*> mProcesses;
    Processes(){}
};

#endif /* PROCESSES_H */

