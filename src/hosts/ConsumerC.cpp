#include "hosts/ConsumerC.h"

using namespace std::literals;

void ConsumerC::consume([[maybe_unused]] int value) {
    std::this_thread::sleep_for(600ms);
}

std::string_view ConsumerC::name() const {
    return "consumer-c"sv;
}
