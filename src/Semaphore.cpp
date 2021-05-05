#include "Semaphore.h"

#include <system_error>

#ifdef _WIN32

#include <windows.h>

[[noreturn]] void throwSystemError(const char* what) {
    throw std::system_error{
        static_cast<int>(GetLastError()), std::system_category(), what
    };
}

struct Semaphore::Impl {
public:
    void init(int value) {
        sem = CreateSemaphore(nullptr, value, 1, nullptr);
        if(sem == nullptr) {
            throwSystemError("CreateSemaphore failed");
        }
    }
    
    void destory() noexcept {
        CloseHandle(sem);
    }

    void p() {
        const DWORD result = WaitForSingleObject(sem, INFINITE);
        if(result == WAIT_FAILED) {
            throwSystemError("WaitForSingleObject failed");
        }
    }

    void v() {
        const BOOL result = ReleaseSemaphore(sem, 1, nullptr);
        if(result == 0) {
            throwSystemError("ReleaseSemaphore failed");
        }
    }

private:
    HANDLE sem;
};

#else // ^^^ _WIN32 / !_WIN32 vvv

#include <errno.h> 
#include <fcntl.h> 
#include <pthread.h> 
#include <semaphore.h>
#include <string.h> 
#include <sys/types.h> 
#include <sys/stat.h>
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
    
    void destory() noexcept {
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

#endif // ifndef _WIN32

Semaphore::Semaphore(int value) : impl{std::make_unique<Impl>()} {
    impl->init(value);
}

Semaphore::~Semaphore() {
    impl->destory();
}

void Semaphore::p() {
    impl->p();
}

void Semaphore::v() {
    impl->v();
}
