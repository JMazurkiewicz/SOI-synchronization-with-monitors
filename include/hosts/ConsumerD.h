#ifndef CONSUMERD_H
#define CONSUMERD_H

#include "Consumer.h"

class ConsumerD final : public Consumer {
public:
    using Consumer::Consumer;

private:
    void consume(int value) override final;
    std::string_view name() const override;
};

#endif
