
#ifndef PAGETABLE_H
#define PAGETABLE_H
#include <map>
#include "TableEntry.h"
class PageTable {
public:
    static PageTable& getInstance() {
        static PageTable instance;
        return instance;
    }
    PageTable(const PageTable& orig) = delete;
    void operator=(PageTable const&) = delete;
    virtual ~PageTable();
    
    std::map<int, TableEntry*>* getPageTable();
private:
    std::map<int, TableEntry*>* mTable;
    PageTable(){
        mTable = new std::map<int, TableEntry*>();
    }
};

#endif /* PAGETABLE_H */

