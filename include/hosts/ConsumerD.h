#ifndef CONSUMERD_H
#define CONSUMERD_H

#include "Consumer.h"

class ConsumerD final : public Consumer {
public:
    using Consumer::Consumer;

private:
    std::string_view name() const override;
};

#endif
