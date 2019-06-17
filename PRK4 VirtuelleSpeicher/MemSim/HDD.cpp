/*Ein Backup-Speicher, d.h. eine Festplatte.  
Sie muss mindestens alle Seiten, die nicht eingelagert sind, speichern, und zwar für alle Prozessen. 
Sie darf mehr speichern. Die "Festplatte" ist auch kaum mehr als eine Array von Bytes. 
Allerdings sollten die Seiten jeder Prozesse mit Inhalt initialisiert werden, 
sodass wir die Seiten der verschiedenen Prozesse auseinander halten können, s.o.*/
#include "HDD.h"

HDD::~HDD() {
    delete[] mStorage;
}

void HDD::init(int size) {
    mSize = size;
    mStorage = new int[mSize];
}

int HDD::get(int index) const {
    return mStorage[index];
}

void HDD::put(int value, int index) {
    mStorage[index] = value;
}

int HDD::size() const {
    return mSize;
}
