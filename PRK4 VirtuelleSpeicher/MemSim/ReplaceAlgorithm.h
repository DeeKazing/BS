#ifndef REPLACEALGORITHM_H
#define REPLACEALGORITHM_H
#include "Process.h"
extern int pageSize;
extern int pageCount;

class ReplaceAlgorithm {
public:
    ReplaceAlgorithm();
    virtual ~ReplaceAlgorithm();
    
    virtual int replace(int vAddress, Process* process) = 0;
private:
};

#endif /* REPLACEALGORITHM_H */

