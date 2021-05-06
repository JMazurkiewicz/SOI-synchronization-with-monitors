#ifndef CONSUMERC_H
#define CONSUMERC_H

#include "Consumer.h"

class ConsumerC final : public Consumer {
public:
    using Consumer::Consumer;

private:
    void consume(int value) override final;
    std::string_view name() const override final;
};

#endif
