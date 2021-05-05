#include "SyncQueue.h"

SyncQueue::SyncQueue(std::size_t maxSize)
    : maxSize{maxSize} { }

std::size_t SyncQueue::size() const {
    return queue.size();
}
