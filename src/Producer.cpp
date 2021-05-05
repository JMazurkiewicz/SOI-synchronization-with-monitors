#include "Producer.h"

#include "AsyncPrint.h"
#include "hosts/ProducerA.h"
#include "hosts/ProducerB.h"
#include "SyncQueue.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

Producer::Producer(SyncQueue& queue1, SyncQueue& queue2)
    : queue1{queue1}, queue2{queue2}, messageId{0},
      receiver{nullptr}, value{0}, lastQueueSize{0} { }

void Producer::run() {
    while(messageId < MAX_SENT_DATA) {
        receiver = (messageId % 2 == 0 ? &queue1 : &queue2);

        value = produce();
        lastQueueSize = receiver->push(value);
        
        log();
        ++messageId;
    }
}

void Producer::log() const {
    std::ostringstream sstream;

    sstream << std::setfill('0');
    const std::time_t now = std::time(nullptr);

    sstream << '[' << std::put_time(std::localtime(&now), "%H:%M:%S") << "] ";
    sstream << name() << ": wysłano wiadomość nr " << std::setw(4) << messageId+1;
    sstream << " o wartości \"" << value << "\" [adres kolejki: " << receiver;
    sstream << ", rozmiar kolejki: " << lastQueueSize << "]\n";

    asyncPrint(sstream.str());
}

std::string_view guessProducer(int value) {
    return (value % 3 == 0) ? ProducerA::NAME : ProducerB::NAME;
}
