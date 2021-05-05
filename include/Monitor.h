#ifndef MONITOR_H
#define MONITOR_H

#include "Semaphore.h"

class Condition;

class Monitor {
public:
    Monitor();

    Monitor(const Monitor&) = delete;
    Monitor& operator=(const Monitor&) = delete;

    void enter();
    void leave();
    
    void wait(Condition& cond);
    void signal(Condition& cond);

private:
    Semaphore sem;
};

#endif
