#include "hosts/ConsumerD.h"

using namespace std::literals;

void ConsumerD::consume([[maybe_unused]] int value) {
    std::this_thread::sleep_for(500ms);
}

std::string_view ConsumerD::name() const {
    return "consumer-d"sv;
}
