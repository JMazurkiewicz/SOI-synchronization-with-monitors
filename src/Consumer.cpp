#include "Consumer.h"

#include "AsyncPrint.h"
#include "Producer.h"
#include "SyncQueue.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

Consumer::Consumer(SyncQueue& queue)
    : queue{queue}, messageId{0},
      value{0}, queueSize{0} { }

void Consumer::run() {
    while(messageId < MAX_SENT_DATA) {
        std::tie(value, queueSize) = queue.pop();
        log();

        std::this_thread::sleep_for(CONSUMER_COOLDOWN);
        ++messageId;
    }
}

void Consumer::log() const {
        std::ostringstream sstream;

    sstream << std::setfill('0');
    const std::time_t now = std::time(nullptr);

    sstream << '[' << std::put_time(std::localtime(&now), "%H:%M:%S") << "] ";
    sstream << name() << ": otrzymano wiadomość nr " << std::setw(4) << messageId+1;
    sstream << " o treści \"" << value << "\" [adres kolejki: " << &queue;
    sstream << ", rozmiar kolejki: " << queueSize;
    sstream << ", nadawca: " << guessProducer(value) << "]\n";

    asyncPrint(sstream.str());
}
