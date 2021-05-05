#include "Semaphore.h"

#ifdef _WIN32

#include <windows.h>

struct Semaphore::Impl {
public:
    void init(int value) {
        sem = CreateSemaphore(nullptr, value, 1, nullptr);
    }
    
    void destory() {
        CloseHandle(sem);
    }

    void p() {
        WaitForSingleObject(sem, INFINITE);
    }

    void v() {
        ReleaseSemaphore(sem, 1, nullptr);
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
#include <system_error>
#include <unistd.h>

struct Semaphore::Impl {
public:
    void init(int value) {
        if(sem_init(&sem, 0, value) != 0) {
            throw std::system_error{errno, std::system_category(), "sem_init failed"};
        }
    }
    
    void destory() {
        sem_destroy(&sem); 
    }

    void p() {
        if(sem_wait(&sem) != 0) {
            throw std::system_error{errno, std::system_category(), "sem_wait failed"};
        }
    }

    void v() {
        if(sem_post(&sem) != 0) {
            throw std::system_error{errno, std::system_category(), "sem_post failed"};
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
