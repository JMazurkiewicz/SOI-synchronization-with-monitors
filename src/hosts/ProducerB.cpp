#include "hosts/ProducerB.h"

using namespace std::chrono_literals;

std::string_view ProducerB::name() const {
    return NAME;
}

int ProducerB::produce() {
    ++val;
    if(val % 3 == 0) {
        ++val;
    }

    std::this_thread::sleep_for(500ms);
    return val;
}
