#ifndef MMU_H
#define MMU_H
#include "OS.h"
extern int pageSize;
extern int pageCount;

class MMU {
public:
    MMU(OS* os);
    virtual ~MMU();
    
    int translate(int vAddress, bool modify);
private:
    OS* mOS;
};

#endif /* MMU_H */

