#ifndef QUEUE_H
#define QUEUE_H

#include "Condition.h"
#include "Monitor.h"
#include "MonitorGuard.h"

#include <functional>
#include <queue>
#include <string>

class SyncQueue : protected Monitor {
public:
    explicit SyncQueue(std::size_t maxSize, std::string name);

    SyncQueue(const SyncQueue&) = delete;
    SyncQueue& operator=(const SyncQueue&) = delete;

    template<typename Callback>
    void push(int value, Callback&& callback) {
        MonitorGuard guard{*this};
        if(size() == maxSize) {
            wait(full);
        }

        queue.push(value);
        std::invoke(std::forward<Callback>(callback), *this);

        if(size() == 1) {
            signal(empty);
        }
    }

    template<typename Callback>
    void pop(Callback&& callback) {
        MonitorGuard guard{*this};
        if(size() == 0) {
            wait(empty);
        }

        const int value = queue.front();
        queue.pop();
        std::invoke(std::forward<Callback>(callback), *this, value);

        if(size() == maxSize-1) {
            signal(full);
        }
    }

    std::size_t size() const;
    std::string_view getName() const;

private:
    const std::size_t maxSize;
    std::string name;

    Condition full;
    Condition empty;

    std::queue<int> queue;
};

#endif
