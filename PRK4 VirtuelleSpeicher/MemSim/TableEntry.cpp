#include "TableEntry.h"

TableEntry::TableEntry(int address, int ownerPid) : mAddress(address), mOwnerPid(ownerPid), mReferenced(false), mModified(false), mPresent(true) {
}

TableEntry::~TableEntry() {
}

bool TableEntry::isPresent() const {
    return mPresent;
}

void TableEntry::setReferenced(bool referenced) {
    mReferenced = referenced;
}

bool TableEntry::wasReferenced() const {
    return mReferenced;
}

bool TableEntry::wasModified() const {
    return mModified;
}

void TableEntry::setPresent(bool present) {
    mPresent = present;
}

void TableEntry::reference() {
    mReferenced = true;
}

void TableEntry::modify() {
    mModified = true;
}

int TableEntry::getOwner() const {
    return mOwnerPid;
}

int TableEntry::getAddress() const {
    return mAddress;
}