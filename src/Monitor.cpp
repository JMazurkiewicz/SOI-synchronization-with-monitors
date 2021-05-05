#include "Monitor.h"

#include "Condition.h"

void Monitor::enter() {
	sem.p();
}

void Monitor::leave() {
	sem.v();
}

void Monitor::wait(Condition& cond) {
    ++cond.waitingThreadsCount;
    leave();
    cond.wait();
}

void Monitor::signal(Condition& cond) {
    if(cond.signal()) {
        enter();
    }
}
