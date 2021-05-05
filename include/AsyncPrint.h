#ifndef ASYNCPRINT_H
#define ASYNCPRINT_H

#include <iostream>
#include <mutex>

template<typename... Args>
void asyncPrint(const Args&... args) {
    static std::mutex m;

    std::lock_guard guard{m};
    (std::cout << ... << args);
}

#endif