#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::to_string;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes(int n) { 
  //std::vector<Process> P_={};
  //std::vector<Process> processes_ = {}
  std::vector<int> Pids=LinuxParser::Pids();
  for(int i=0; i<n; i++){
    Process new_P;
    new_P.pid=Pids[i];
    new_P.user=LinuxParser::User(Pids[i]);
    //new_P.user=to_string(LinuxParser::UpTime(Pids[i]));
    new_P.ram=LinuxParser::Ram(Pids[i]);
    new_P.cmd=LinuxParser::Command(Pids[i]);
    new_P.uptime=LinuxParser::UpTime(Pids[i]);
    new_P.cpu_uti=LinuxParser::Cpu(Pids[i]);
    
    processes_.push_back(new_P);
  }
  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime();}