#ifndef INCLUDE_SUB_UTILS_H
#define INCLUDE_SUB_UTILS_H
#include <string>
#include "../SubLine/SubLine.h"

class SubUtils {
public:
    // Convert "01:00:01,600" to milliseconds.
    // Convert "0:02:40.65" to milliseconds
    // Will try all patterns. 
    // Return false if fail to parse
    static bool hourToMilliseconds(const std::string& timestr, unsigned int& out, enum SUB_TYPE subType);

    // Convert milliseconds to "01:00:01,600"
    static bool millisecondsToHour(unsigned int ms, std::string& out, enum SUB_TYPE subType);

    // Count words in a sentence, separated by space/linebreak.
    static int countWords(const std::string& sentence);

    static int CRLFtoLF(std::string& str);
private:
    static bool hourToMilliseconds_srt(const std::string& timestr, unsigned int& out);
    static bool hourToMilliseconds_ass(const std::string& timestr, unsigned int& out);

    // Make number string "2" appear like "02".
    static std::string zeroPrefix(const std::string& num, int maxlen);
};
#endif