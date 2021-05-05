#ifndef PRODUCER_H
#define PRODUCER_H

#include "Host.h"

class SyncQueue;

class Producer : public Host {
public:
    explicit Producer(SyncQueue& queue1, SyncQueue& queue2);

    Producer(const Producer&) = delete;
    Producer& operator=(const Producer&) = delete;

protected:
    virtual int produce() = 0;

private:
    void run() override final;
    void log() const;

    SyncQueue& queue1;
    SyncQueue& queue2;
};

std::string_view guessProducer(int value);

#endif
