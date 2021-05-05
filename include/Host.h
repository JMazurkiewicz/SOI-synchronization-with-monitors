#ifndef HOST_H
#define HOST_H

#include <chrono>
#include <thread>

class Host {
public:
    Host(const Host&) = delete;
    Host& operator=(const Host&) = delete;

    void invokeDelayed(const std::chrono::milliseconds& milli);
    void join();

protected:
    static constexpr int MAX_SENT_DATA = 100;
    static_assert(MAX_SENT_DATA % 2 == 0);

    Host() = default;
    virtual ~Host() = default;

    virtual std::string_view name() const = 0;
    virtual void run() = 0;

private:
    std::thread thread;
};

#endif
