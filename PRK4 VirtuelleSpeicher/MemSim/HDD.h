#ifndef HDD_H
#define HDD_H

extern int pageSize;
extern int pageCount;

class HDD {
public:
    static HDD& getInstance() {
        static HDD instance;
        return instance;
    }
    HDD(const HDD& orig) = delete;
    void operator=(HDD const&) = delete;
    virtual ~HDD();
    
    void init(int size);
    int get(int index) const;
    void put(int value, int index);
    int size() const;
private:
    int mSize;
    int* mStorage;
    HDD(){}
};

#endif /* HDD_H */

