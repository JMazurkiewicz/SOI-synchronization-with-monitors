#include "AsyncPrint.h"

#include <iostream>
#include <mutex>

void asyncPrintImpl(std::string_view str) {
    static std::mutex m;
    std::lock_guard guard{m};
    std::cout << str << std::flush;
}
