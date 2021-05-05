cmake_minimum_required(VERSION 3.10)

project("SOI - monitors")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES 
    src/Condition.cpp
    src/Consumer.cpp
    src/Host.cpp
    src/Main.cpp
    src/Monitor.cpp
    src/MonitorGuard.cpp
    src/Producer.cpp
    src/Semaphore.cpp
    src/SyncQueue.cpp

    src/hosts/ConsumerC.cpp
    src/hosts/ConsumerD.cpp
    src/hosts/ProducerA.cpp
    src/hosts/ProducerB.cpp
)

add_executable(SoiMonitors ${SOURCES})

if(UNIX)
    target_link_libraries(SoiMonitors rt)
    target_link_libraries(SoiMonitors pthread)
endif()

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

target_include_directories(SoiMonitors PUBLIC include)
