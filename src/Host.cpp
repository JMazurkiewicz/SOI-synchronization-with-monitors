#include "Host.h"

void Host::invokeDelayed(const std::chrono::milliseconds& milli) {
    thread = std::thread{[this, milli] {
        std::this_thread::sleep_for(milli);
        this->run();
    }};
}

void Host::join() {
    if(thread.joinable()) {
        thread.join();
    }
}
