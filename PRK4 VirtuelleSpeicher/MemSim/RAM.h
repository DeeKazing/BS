#ifndef RAM_H
#define RAM_H

extern int pageSize;
extern int pageCount;

class RAM {
public:
    static RAM& getInstance() {
        static RAM instance;
        return instance;
    }
    RAM(const RAM& orig) = delete;
    void operator=(RAM const&) = delete;
    virtual ~RAM();
    
    void init(int size);
    int get(int index) const;
    void put(int value, int index);
    int size() const;
private:
    int mSize;
    int* mMemory;
    RAM(){}
};

#endif /* RAM_H */

