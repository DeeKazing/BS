#include "BubbleSort.h"

BubbleSort::BubbleSort() : AddressGenerator(), mAddress(0) {
}

BubbleSort::~BubbleSort() {
}

int BubbleSort::generate() {
    mAddress = (mAddress+1) % (pageSize*pageCount);
    return mAddress;
}