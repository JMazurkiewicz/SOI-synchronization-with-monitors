cmake_minimum_required(VERSION 3.10)

project("SOI-Monitors" LANGUAGES CXX)

add_executable(
    SoiMonitors

    src/AsyncPrint.cpp
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

find_package(Threads REQUIRED)
target_compile_features(SoiMonitors PUBLIC cxx_std_17)
target_link_libraries(SoiMonitors PRIVATE Threads::Threads)
target_include_directories(SoiMonitors PUBLIC include)

if(APPLE) # OS X doesn't support unnamed semaphores, so we need to use C++20 ones.
    target_compile_features(SoiMonitors PRIVATE cxx_std_20)
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(SoiMonitors PRIVATE rt)
endif()

if(MSVC)
    target_compile_definitions(SoiMonitors PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
