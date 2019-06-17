/*Ein Hauptspeicher (RAM).  
Ein Speicher mit der Große von 1 Kilobyte würde anfangs reichen.  
Konzeptuell ist der Hauptspeicher nicht viel mehr als eine Array von Bytes.
*/

#include "RAM.h"
#include <algorithm>

RAM::~RAM() {
    delete[] mMemory;
}

void RAM::init(int size) {
    mSize = size;
    mMemory = new int[mSize];
    std::fill_n(mMemory, mSize, -1);
}

int RAM::get(int index) const {
    return mMemory[index];
}

void RAM::put(int value, int index) {
    mMemory[index] = value;
}

int RAM::size() const {
    return mSize;
}