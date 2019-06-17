/*
Die Seitentabellen. Jedes Prozess hat eine eigene Seitentabelle. 
Die Seitentabelle des aktuellen Prozesses ist die aktuelle Seitentabelle, und wird von der MMU verwendet.  
Das Betriebssystem darf auf alle Seitentabellen zugreifen, falls notwendig.*/

#include "PageTable.h"
#include "TableEntry.h"

PageTable::~PageTable() {
}

std::map<int, TableEntry*>* PageTable::getPageTable() {
    return mTable;
}
