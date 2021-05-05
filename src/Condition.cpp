#include "Condition.h"

Condition::Condition() : sem{0}, waitingThreadsCount{0} { }

void Condition::wait() {
    sem.p();
}

bool Condition::signal() {
    if(waitingThreadsCount != 0) {
        --waitingThreadsCount;
        sem.v();
        return true;
    }
    return false;
}