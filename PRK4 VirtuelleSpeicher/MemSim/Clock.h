#ifndef CLOCK_H
#define CLOCK_H
#include "ReplaceAlgorithm.h"
#include "Process.h"
class Clock : public ReplaceAlgorithm {
public:
    Clock();
    virtual ~Clock();
    
    int replace(int vAddress, Process* process);
private:
    int mHead;
};

#endif /* CLOCK_H */

