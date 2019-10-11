#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  int hour=seconds/3600;
  int minute=(seconds%3600)/60;
  int second=seconds%60;
  string return_time;
  if (hour<10){
    return_time=return_time+'0';
  }
  return_time+=std::to_string(hour)+':';
  if (minute<10){
    return_time=return_time+'0';
  }
  return_time+=std::to_string(minute)+':';
  if (second<10){
    return_time=return_time+'0';
  }
  return_time+=std::to_string(second);
  return return_time;
}