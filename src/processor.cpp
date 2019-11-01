#include "processor.h"

Processor::Processor()
{
    lastIdleJiffies_ = 0.0;
    lastTotalJiffies_ = 0.0;
}

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    long idleJiffies = LinuxParser::IdleJiffies();
    long totalJiffies = LinuxParser::Jiffies();

    int deltaIdleJiffies = idleJiffies - lastIdleJiffies_;
    int deltaTotalJiffies = totalJiffies - lastTotalJiffies_;

    float deltaCpuUtilization = float(deltaTotalJiffies - deltaIdleJiffies)/deltaTotalJiffies;

    lastIdleJiffies_ = idleJiffies;
    lastTotalJiffies_ = totalJiffies;

    return deltaCpuUtilization;
}