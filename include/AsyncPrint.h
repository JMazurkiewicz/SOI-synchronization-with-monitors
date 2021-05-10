#ifndef ASYNCPRINT_H
#define ASYNCPRINT_H

#include <sstream>
#include <string_view>

template<typename... Args>
void asyncPrint(const Args&... args) {
    std::ostringstream sstream;
    (sstream << ... << args);
    
    void asyncPrintImpl(std::string_view);
    asyncPrintImpl(sstream.str());
}

#endif
