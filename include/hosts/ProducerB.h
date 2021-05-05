#ifndef PRODUCERB_H
#define PRODUCERB_H

#include "Producer.h"

class ProducerB final : public Producer {
public:
    static constexpr std::string_view NAME{"producer-b"};

    using Producer::Producer;

private:
    std::string_view name() const override;
    int produce() override;

    int val = 0;
};

#endif