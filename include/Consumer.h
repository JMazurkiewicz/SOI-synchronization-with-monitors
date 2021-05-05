#ifndef CONSUMER_H
#define CONSUMER_H

#include "Host.h"

#include <chrono>

class SyncQueue;

class Consumer : public Host {
public:
    static constexpr std::chrono::milliseconds CONSUMER_COOLDOWN{1000};

    explicit Consumer(SyncQueue& queue);

    Consumer(const Consumer&) = delete;
    Consumer& operator=(const Consumer&) = delete;

private:
    void run() override final;

    SyncQueue& queue;
};

#endif