#include "MonitorGuard.h"

#include "Monitor.h"

MonitorGuard::MonitorGuard(Monitor& monitor) : monitor{monitor} {
    monitor.enter();
}

MonitorGuard::~MonitorGuard() {
    monitor.leave();
}
