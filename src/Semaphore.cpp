#include "Semaphore.h"

#if defined(_WIN32)

#include <system_error>
#include <windows.h>

[[noreturn]] void throwSystemError(const char* what) {
    throw std::system_error{
        static_cast<int>(GetLastError()), std::system_category(), what
    };
}

struct Semaphore::Impl {
public:
    void init(int value) {
        if(CreateSemaphore(nullptr, static_cast<LONG>(value), 1, nullptr) == nullptr) {
            throwSystemError("CreateSemaphore failed");
        }
    }
    
    void destroy() noexcept {
        CloseHandle(sem);
    }

    void p() {
        if(WaitForSingleObject(sem, INFINITE) == WAIT_FAILED) {
            throwSystemError("WaitForSingleObject failed");
        }
    }

    void v() {
        if(ReleaseSemaphore(sem, 1, nullptr) == 0) {
            throwSystemError("ReleaseSemaphore failed");
        }
    }

private:
    HANDLE sem;
};

#elif defined(__linux__) // ^^^ _WIN32 / __linux__ vvv

#include <errno.h> 
#include <fcntl.h> 
#include <pthread.h> 
#include <semaphore.h>
#include <string.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <system_error>
#include <unistd.h>

[[noreturn]] void throwSystemError(const char* what) {
    throw std::system_error{errno, std::system_category(), what};
}

struct Semaphore::Impl {
public:
    void init(int value) {
        if(sem_init(&sem, 0, value) != 0) {
            throwSystemError("sem_init failed");
        }
    }
    
    void destroy() noexcept {
        sem_destroy(&sem); 
    }

    void p() {
        if(sem_wait(&sem) != 0) {
            throwSystemError("sem_wait failed");
        }
    }

    void v() {
        if(sem_post(&sem) != 0) {
            throwSystemError("sem_post failed");
        }
    }

private:
    sem_t sem;
};

#else // ^^^ __linux__ / C++20 semaphore vvv

#include <version>

#if __cpp_lib_semaphore < 201907L
#  error C++20 semaphores are not supported by this compiler.
#else
#  include <optional>
#  include <semaphore>
#endif

struct Semaphore::Impl {
public:
    using sem_t = std::counting_semaphore<>;

    void init(int value) {
        sem.emplace(static_cast<std::ptrdiff_t>(value));
    }
    
    void destroy() noexcept {
        sem.reset();
    }

    void p() {
        sem->acquire();
    }

    void v() {
        sem->release();
    }

private:
    std::optional<sem_t> sem;
};

#endif // if defined(_WIN32)

Semaphore::Semaphore(int value) : impl{std::make_unique<Impl>()} {
    impl->init(value);
}

Semaphore::~Semaphore() {
    impl->destroy();
}

void Semaphore::p() {
    impl->p();
}

void Semaphore::v() {
    impl->v();
}
