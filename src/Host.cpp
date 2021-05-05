#include "Host.h"

#include "AsyncPrint.h"

void Host::invokeDelayed(const std::chrono::milliseconds& milli) {
    thread = std::thread{[this, milli] {
        std::this_thread::sleep_for(milli);
        this->logStart();
        this->run();
        this->logEnd();
    }};
}

void Host::join() {
    if(thread.joinable()) {
        thread.join();
    }
}

void Host::logStart() const {
    asyncPrint("Host '", name(), "' został uruchomiony w wątku ", std::this_thread::get_id(), '\n');
}

void Host::logEnd() const {
    asyncPrint("Host '", name(), "' zakończył pracę\n");
}
