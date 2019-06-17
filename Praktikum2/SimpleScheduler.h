
#ifndef SIMPLESCHEDULER_H
#define SIMPLESCHEDULER_H
#include "Scheduler.h"

class SimpleScheduler : public Scheduler{
public:
    SimpleScheduler();
    Process* next(Process* aktuellerProzess) override;
    void block(Process* aktuellerProzess) override;
    void unblock() override;
    void add(Process* newProcess) override;
};

#endif /* SIMPLESCHEDULER_H */

