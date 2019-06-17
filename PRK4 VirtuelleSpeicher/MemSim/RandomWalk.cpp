#include "RandomWalk.h"
#include <random>
#include <math.h>

RandomWalk::RandomWalk() : AddressGenerator(), mAddress(0) {
}

RandomWalk::~RandomWalk() {
}

int RandomWalk::generate() {
    int offset = pow(-1, std::rand() % 2) * (std::rand() % pageSize * pageCount / 4);
    int modulus = (pageSize * pageCount);
    mAddress = mAddress + offset;
    mAddress = (mAddress % modulus + modulus) % modulus;
    return mAddress;
}