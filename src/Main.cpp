#include "Producer.h"

#include "hosts/ProducerA.h"
#include "hosts/ProducerB.h"
#include "hosts/ConsumerC.h"
#include "hosts/ConsumerD.h"
#include "SyncQueue.h"

#include <chrono>
#include <iostream>
#include <thread>

int main() {
    using namespace std::chrono_literals;

    static constexpr std::size_t MAX_QUEUE_SIZE = 20;

    std::ios_base::sync_with_stdio(false);
    std::cout << std::unitbuf;

    SyncQueue cQueue{MAX_QUEUE_SIZE};
    SyncQueue dQueue{MAX_QUEUE_SIZE};

    ProducerA producerA{cQueue, dQueue};
    producerA.invokeDelayed(50ms);

    ProducerB producerB{cQueue, dQueue};
    producerB.invokeDelayed(50ms);

    ConsumerC consumerC{cQueue};
    consumerC.invokeDelayed(300ms);

    ConsumerD consumerD{dQueue};
    consumerD.invokeDelayed(300ms);

    consumerD.join();
    consumerC.join();
    producerB.join();
    producerA.join();
}
