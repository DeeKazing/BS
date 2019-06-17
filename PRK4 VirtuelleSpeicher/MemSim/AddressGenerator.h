#ifndef ADDRESSGENERATOR_H
#define ADDRESSGENERATOR_H
extern int pageSize;
extern int pageCount;

class AddressGenerator {
public:
    AddressGenerator();
    virtual ~AddressGenerator();
    
    virtual int generate() = 0;
private:
    int mAddress;
};

#endif /* ADDRESSGENERATOR_H */

