#include "SyncQueue.h"

SyncQueue::SyncQueue(std::size_t maxSize, std::string name)
    : maxSize{maxSize}, name{std::move(name)} { }

std::size_t SyncQueue::size() const {
    return queue.size();
}

std::string_view SyncQueue::getName() const {
    return name;
}
