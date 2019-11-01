#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
    string line;
    string key;
    string value;
    int memTotal;
    int memAvailable;

    std::ifstream filestream(kProcDirectory + kMeminfoFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            if (key == "MemTotal:")
                memTotal = stoi(value);
            else if (key == "MemAvailable:")
                memAvailable = stoi(value);
        }
        return float(memAvailable) / memTotal;
    }
    return 0;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  string line;
  string key;
  string value;

  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> key >> value;
    return stoi(key);
  }

  return 0;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
    std::ifstream filestream(kProcDirectory + kStatFilename);
    string line;
    string cpu;
    string user;
    string nice;
    string system;
    string idle;
    string iowait;
    string irq;
    string softirq;
    string steal;
    string guest;
    string guest_nice;

    if (filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

        long user_long = stol(user);
        long nice_long = stol(nice);
        long system_long = stol(system);
        long idle_long = stol(idle);
        long nowait_long = stol(iowait);
        long irq_long = stol(irq);
        long softirq_long = stol(softirq);
        long steal_long = stol(steal);
        long guest_long = stol(guest);
        long guest_nice_long = stol(guest_nice);

        long total_long = user_long + nice_long + system_long + idle_long + nowait_long +
                irq_long + softirq_long + steal_long + guest_long + guest_nice_long;
        return total_long;
    }
    return 0;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
    std::ifstream filestream(kProcDirectory + kStatFilename);
    string line;
    string cpu;
    string user;
    string nice;
    string system;
    string idle;
    string iowait;
    string irq;
    string softirq;
    string steal;
    string guest;
    string guest_nice;

    if (filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;

        long user_long = stol(user);
        long nice_long = stol(nice);
        long system_long = stol(system);
        long irq_long = stol(irq);
        long softirq_long = stol(softirq);
        long steal_long = stol(steal);
        long guest_long = stol(guest);
        long guest_nice_long = stol(guest_nice);

        long active_long = user_long + nice_long + system_long + irq_long + softirq_long +
                steal_long + guest_long + guest_nice_long;
        return active_long;
    }
    return 0;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
    std::ifstream filestream(kProcDirectory + kStatFilename);
    string line;
    string cpu;
    string user;
    string nice;
    string system;
    string idle;
    string iowait;
    if (filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> cpu >> user >> nice >> system >> idle >> iowait;
        return stoi(idle) + stoi(iowait);
    }
    return 0;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::ifstream filestream(kProcDirectory + kStatFilename);
  string line;
  string key;
  string value;
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          if (std::all_of(value.begin(), value.end(), isdigit)) {
            int num_running_procs = stoi(value);
            return num_running_procs;
          }
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::ifstream filestream(kProcDirectory + kStatFilename);
  string line;
  string key;
  string value;
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          if (std::all_of(value.begin(), value.end(), isdigit)) {
            int num_running_procs = stoi(value);
            return num_running_procs;
          }
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid)
{
    string line;
    string cmdLine;
    string value;
    string uid;

    std::ifstream filestream(kProcDirectory + "/" + to_string(pid) + kCmdlineFilename);
    if (filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> cmdLine;
        return cmdLine;
    }
    return string();
}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
    LinuxParser::kProcDirectory + "/" + to_string(pid) + LinuxParser::kStatusFilename;
    string line;
    string key;
    string value;
    int ram_long;

    std::ifstream filestream(kProcDirectory + kMeminfoFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            if (key == "VmSize:") {
                ram_long = stoi(value);
                int mb_long = int(float(ram_long) / 1024); // convert to MB
                return to_string(mb_long);
            }
        }
    }
    return string();
}

// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
    string line;
    string key;
    string value;
    string uid;

    std::ifstream filestream(kProcDirectory + "/" + to_string(pid) + kStatusFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> value;
            if (key == "Uid:")
                uid = value;
        }
        return uid;
    }
    return string();
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
    string uid = Uid(pid);

    string line;
    string key;
    string x;
    string value;
    string username;

    std::ifstream filestream(kPasswordPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            linestream >> key >> x >> value;
            if (value == uid) {
                username = key;
                return username;
            }
        }
    }
    return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long int LinuxParser::UpTime(int pid) {
    std::ifstream filestream(LinuxParser::kProcDirectory + "/" + to_string(pid) + LinuxParser::kStatFilename);
    string line;
    string pidstr;
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
        linestream >> pidstr >> comm >> state >> ppid >> pgrp >> session >> tty_nr >> tpg_id >> flags >>
                   minflt >> cminflt >> majflt >> cmajflt >> utime >> stime >> cutime >> cstime >> priority >> nice >>
                   num_threads >> itrealvalue >> starttime;

        long starttime_long = stol(starttime);

        long Hertz = sysconf(_SC_CLK_TCK);
        long seconds_long = float(starttime_long / Hertz);

        return seconds_long;
    }
    return 0;
}