#ifndef ASYNCPRINT_H
#define ASYNCPRINT_H

#include <iostream>
#include <sstream>
#include <mutex>

template<typename... Args>
void asyncPrint(const Args&... args) {
    static std::mutex m;
    std::lock_guard guard{m};

    std::ostringstream sstream;
    (sstream << ... << args);
    std::cout << sstream.str() << std::flush;
}

#endif