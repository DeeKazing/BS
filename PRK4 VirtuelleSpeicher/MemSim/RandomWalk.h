#ifndef RANDOMWALK_H
#define RANDOMWALK_H
#include "AddressGenerator.h"
class RandomWalk : public AddressGenerator {
public:
    RandomWalk();
    virtual ~RandomWalk();
    
    int generate();
private:
    int mAddress;
};

#endif /* RANDOMWALK_H */

