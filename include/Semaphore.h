#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <memory>

class Semaphore {
public:
    explicit Semaphore(int value);
    ~Semaphore();

    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;

    void p();
    void v();

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif
