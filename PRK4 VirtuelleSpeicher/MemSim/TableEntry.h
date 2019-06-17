#ifndef TABLEENTRY_H
#define TABLEENTRY_H

extern int pageSize;
extern int pageCount;

class TableEntry {
public:
    TableEntry(int address, int ownerPid);
    virtual ~TableEntry();
    
    void setPresent(bool present);
    void setReferenced(bool referenced);
    
    void reference();
    void modify();
    
    bool isPresent() const;
    bool wasReferenced() const;
    bool wasModified() const;
    
    int getAddress() const;
    int getOwner() const;
private:
    int mAddress;
    bool mPresent;
    bool mReferenced;
    bool mModified;
    int mOwnerPid;
    
};

#endif /* TABLEENTRY_H */

