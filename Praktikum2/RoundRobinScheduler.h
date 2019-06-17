#ifndef ROUNDROBINSCHEDULER_H
#define ROUNDROBINSCHEDULER_H
#include "Scheduler.h"

class RoundRobinScheduler : public Scheduler {
public:
    RoundRobinScheduler();
    Process* next(Process* aktuellerProzess) override;
    void block(Process* aktuellerProzess) override;
    void unblock() override;
    void add(Process* newProcess) override;
private:
    int quantum;
};

#endif /* ROUNDROBINSCHEDULER_H */

