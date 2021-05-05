#ifndef CONSUMER_H
#define CONSUMER_H

#include "Host.h"

class SyncQueue;

class Consumer : public Host {
public:
    explicit Consumer(SyncQueue& queue);

    Consumer(const Consumer&) = delete;
    Consumer& operator=(const Consumer&) = delete;

private:
    void run() override final;
    void log() const;

    SyncQueue& queue;

    int messageId;
    int value;
    std::size_t queueSize;
};

#endif