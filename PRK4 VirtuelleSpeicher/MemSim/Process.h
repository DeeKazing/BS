/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Process.h
 * Author: Ludwig Samuel
 *
 * Created on January 3, 2019, 4:18 PM
 */

#ifndef PROCESS_H
#define PROCESS_H
#include <map>
#include "TableEntry.h"
extern int pageSize;
extern int pageCount;

class Process {
public:
    Process(int pid);
    virtual ~Process();
    
    int getPid() const;
    std::map<int, TableEntry*>* getTable();
private:
    int mPid;
    std::map<int, TableEntry*>* mTable;
};

#endif /* PROCESS_H */

