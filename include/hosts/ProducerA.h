#ifndef PRODUCERA_H
#define PRODUCERA_H

#include "Producer.h"

#include <random>
#include <string_view>

class ProducerA final : public Producer {
public:
    static constexpr std::string_view NAME{"producer-a"};

    explicit ProducerA(SyncQueue& queue1, SyncQueue& queue2);

private:
    std::string_view name() const override;
    int produce() override;

    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;
};

#endif
