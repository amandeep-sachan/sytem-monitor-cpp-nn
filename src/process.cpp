#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) {
    pid_ = pid;
}

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    std::ifstream filestream(LinuxParser::kProcDirectory + "/" + to_string(pid_) + LinuxParser::kStatFilename);
    string line;
    string pid;
    string comm;
    string state;
    string ppid;
    string pgrp;
    string session;
    string tty_nr;
    string tpg_id;
    string flags;
    string minflt;
    string cminflt;
    string majflt;
    string cmajflt;

    string utime;
    string stime;
    string cutime;
    string cstime;

    string priority;
    string nice;
    string num_threads;
    string itrealvalue;

    string starttime;

    if (filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr >> tpg_id >> flags >>
                   minflt >> cminflt >> majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> priority >> nice >>
                   num_threads >> itrealvalue >> starttime;

        long utime_long = stol(utime);
        long stime_long = stol(stime);
        long cstime_long = stol(cstime);
        long starttime_long = stol(starttime);

        long total_time_long = utime_long + stime_long + cstime_long;
        long Hertz = sysconf(_SC_CLK_TCK);
        long systemUpTime = LinuxParser::UpTime();
        long seconds_long = systemUpTime - float(starttime_long / Hertz);
        float cpu_usage = float(total_time_long / Hertz) / seconds_long;

        return cpu_usage;
    }
    return 0;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { return pid_ > a.pid_; }