#ifndef MONITORGUARD_H
#define MONITORGUARD_H

class Monitor;

class MonitorGuard {
public:
    explicit MonitorGuard(Monitor& monitor);
    ~MonitorGuard();

    MonitorGuard(const MonitorGuard&) = delete;
    MonitorGuard& operator=(const MonitorGuard&) = delete;

private:
    Monitor& monitor;
};

#endif
