#ifndef CONDITION_H
#define CONDITION_H

#include "Semaphore.h"

class Condition {
  friend class Monitor;

public:
    Condition();

    Condition(const Condition&) = delete;
    Condition& operator=(const Condition&) = delete;

    void wait();
    bool signal();

private:
    Semaphore sem;
    int waitingThreadsCount;
};

#endif
