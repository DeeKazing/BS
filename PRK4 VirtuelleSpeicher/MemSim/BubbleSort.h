#ifndef BUBBLESORT_H
#define BUBBLESORT_H
#include "AddressGenerator.h"

class BubbleSort : public AddressGenerator {
public:
    BubbleSort();
    virtual ~BubbleSort();
    
    int generate();
private:
    int mAddress;
};

#endif /* BUBBLESORT_H */

