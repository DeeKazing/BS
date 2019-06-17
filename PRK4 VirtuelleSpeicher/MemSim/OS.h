#ifndef OS_H
#define OS_H
#include <vector>
#include "ReplaceAlgorithm.h"
#include "Process.h"

extern int pageSize;
extern int pageCount;

class OS {
public:
    OS(ReplaceAlgorithm* replaceAlgorithm);
    OS(const OS& orig);
    virtual ~OS();
    
    int handlePageError(int vAddress, Process* process);
private:
    ReplaceAlgorithm* mReplaceAlgorithm;
    int load(int vAddress, Process* process);
    int replace(int vAddress, Process* process);
};

#endif /* OS_H */

