#include <string>
#include <iostream>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long total_seconds) {
    int seconds_in_day_remainder = total_seconds % 86400;
    int hours = int(seconds_in_day_remainder / 86400.0 * 24);
    int minutes = int((((seconds_in_day_remainder / 86400.0) * 24) - hours) * 60);
    int seconds = int((((((seconds_in_day_remainder / 86400.0) * 24) - hours) * 60) - minutes) * 60);

    char buffer[9];
    sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
    return buffer;
}