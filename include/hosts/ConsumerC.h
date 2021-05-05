#ifndef CONSUMERC_H
#define CONSUMERC_H

#include "Consumer.h"

class ConsumerC final : public Consumer {
public:
    using Consumer::Consumer;

private:
    std::string_view name() const override;
};

#endif
