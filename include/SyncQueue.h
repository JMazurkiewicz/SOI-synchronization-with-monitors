#ifndef QUEUE_H
#define QUEUE_H

#include "Condition.h"
#include "Monitor.h"

#include <queue>

class SyncQueue : protected Monitor {
public:
    explicit SyncQueue(std::size_t maxSize);

    SyncQueue(const SyncQueue&) = delete;
    SyncQueue& operator=(const SyncQueue&) = delete;

    std::size_t push(int value);
    std::pair<int, std::size_t> pop();

private:
    std::size_t getSize() const;

    const std::size_t maxSize;

    Condition full;
    Condition empty;

    std::queue<int> queue;
};

#endif
