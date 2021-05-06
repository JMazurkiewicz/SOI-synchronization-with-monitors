#include "Consumer.h"

#include "AsyncPrint.h"
#include "Producer.h"
#include "SyncQueue.h"

#include <ctime>
#include <iomanip>

Consumer::Consumer(SyncQueue& queue)
    : queue{queue} { }

void Consumer::run() {
    for(int i = 0; i < MAX_SENT_DATA; ++i) {
        int theValue = -1;

        queue.pop([&, name = name()](const SyncQueue& queue, int value) mutable {
            const std::time_t now = std::time(nullptr);

            asyncPrint(
                std::setfill('0'),
                std::put_time(std::localtime(&now), "[%T] "),
                name, ": otrzymano wiadomość nr ", std::setw(4), i+1,
                " o treści \"", value,
                "\" [nazwa kolejki: ", queue.getName(),
                ", rozmiar kolejki: ", queue.size(),
                ", nadawca: ", guessProducer(value), "]\n"
            );

            theValue = value;
        });

        consume(theValue);
    }
}
