#include "Producer.h"

#include "AsyncPrint.h"
#include "hosts/ProducerA.h"
#include "hosts/ProducerB.h"
#include "SyncQueue.h"

#include <ctime>
#include <iomanip>
#include <iostream>

Producer::Producer(SyncQueue& queue1, SyncQueue& queue2)
    : queue1{queue1}, queue2{queue2} { }

void Producer::run() {
    for(int i = 0; i < MAX_SENT_DATA; ++i) {
        SyncQueue& receiver = (i % 2 == 0 ? queue1 : queue2);

        const int value = produce();

        receiver.push(value, [&, this](const SyncQueue& queue) {
            const std::time_t now = std::time(nullptr);

            asyncPrint(
                std::setfill('0'),
                std::put_time(std::localtime(&now), "[%T] "),
                name(), ": wysłano wiadomość nr ", std::setw(4), i+1,
                " o wartości \"", value,
                "\" [adres kolejki: ", &queue,
                ", rozmiar kolejki: ", queue.size(), "]\n"
            );
        });
    }
}

std::string_view guessProducer(int value) {
    return (value % 3 == 0) ? ProducerA::NAME : ProducerB::NAME;
}
