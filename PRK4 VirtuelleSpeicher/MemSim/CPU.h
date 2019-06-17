#ifndef CPU_H
#define CPU_H
#include "AddressGenerator.h"
#include "MMU.h"
extern int pageSize;
extern int pageCount;

class CPU {
public:
    CPU(AddressGenerator* addressGenerator, MMU* mmu);
    virtual ~CPU();
    
    void simulate(int steps);
    void printStats() const;
private:
    AddressGenerator* mAddressGenerator;
    MMU* mMMU;
    
    void load(int address);
    void store(int value, int address);
    void changeProcess();
};

#endif /* CPU_H */

