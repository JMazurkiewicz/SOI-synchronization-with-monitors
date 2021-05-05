#include "hosts/ProducerA.h"

using namespace std::chrono_literals;

ProducerA::ProducerA(SyncQueue& queue1, SyncQueue& queue2)
    : Producer(queue1, queue2),
      generator{std::random_device{}()},
      distribution{0, 1000} { }

std::string_view ProducerA::name() const {
    return NAME;
}

int ProducerA::produce() {
    std::this_thread::sleep_for(300ms);
    return 3 * distribution(generator);
}
