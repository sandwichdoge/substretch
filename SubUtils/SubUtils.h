#ifndef INCLUDE_SUB_UTILS_H
#define INCLUDE_SUB_UTILS_H
#include <string>

class SubUtils {
public:
    // Convert "01:00:01,600" to milliseconds.
    // Convert "0:02:40.65" to milliseconds
    // Will try all patterns. 
    // Return false if fail to parse
    static bool hourToMilliseconds(const std::string& timestr, unsigned int& out);
    static bool hourToMilliseconds_srt(const std::string& timestr, unsigned int& out);
    static bool hourToMilliseconds_ass(const std::string& timestr, unsigned int& out);
};
#endif