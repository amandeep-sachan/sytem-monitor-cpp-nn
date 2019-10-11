#include "processor.h"
#include "linux_parser.h"
#include <string>

using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  string line;
  string key;
  float value1,value2,value3,value4,value5,value6,value7;
  float used,total;
  std::ifstream filestream("/proc/stat");
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value1 >> value2 >> value3 >> value4 >> value5 >> value6 >>value7) {
        if (key == "cpu") {
          used=value1+value2+value3+value6+value7;
          total=used+value4+value5;
          return used/total;
        }
        else{
          break;        
        }
      }
    }
  }
}