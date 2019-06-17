#ifndef NRU_H
#define NRU_H
#include "ReplaceAlgorithm.h"
#include "Process.h"
class NRU : public ReplaceAlgorithm{
public:
    NRU();
    virtual ~NRU();
    
    int replace(int vAddress, Process* process);
private:
};

#endif /* NRU_H */

