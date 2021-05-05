#include "Host.h"

#include "AsyncPrint.h"

#include <sstream>

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
    std::ostringstream sstream;
    sstream << "Host '" << name() << "' został uruchomiony w wątku ";
    sstream << std::this_thread::get_id() << '\n';
    asyncPrint(sstream.str());
}

void Host::logEnd() const {
    std::ostringstream sstream;
    sstream << "Host '" << name() << "' zakończył pracę\n";
    asyncPrint(sstream.str());
}
