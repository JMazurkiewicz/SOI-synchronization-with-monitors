#ifndef CONSUMER_H
#define CONSUMER_H

#include "Host.h"

class SyncQueue;

class Consumer : public Host {
public:
    explicit Consumer(SyncQueue& queue);

    Consumer(const Consumer&) = delete;
    Consumer& operator=(const Consumer&) = delete;

protected:
    virtual void consume(int value) = 0;

private:
    void run() override final;

    SyncQueue& queue;
};

#endif