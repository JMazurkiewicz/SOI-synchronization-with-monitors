#include "SyncQueue.h"

#include "MonitorGuard.h"

SyncQueue::SyncQueue(std::size_t maxSize)
    : maxSize{maxSize} { }

std::size_t SyncQueue::push(int value) {
    MonitorGuard guard{*this};
    if(getSize() == maxSize) {
        wait(full);
    }

    queue.push(value);
    const std::size_t size = getSize();

    if(getSize() == 1) {
        signal(empty);
    }

    return size;
}

std::pair<int, std::size_t> SyncQueue::pop() {
    MonitorGuard guard{*this};
    if(getSize() == 0) {
        wait(empty);
    }

    const int value = queue.front();
    queue.pop();
    const std::size_t size = getSize();

    if(getSize() == maxSize-1) {
        signal(full);
    }
    return {value, size};
}

std::size_t SyncQueue::getSize() const {
    return queue.size();
}
