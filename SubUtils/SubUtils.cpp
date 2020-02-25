#include "SubUtils.h"
#include "../CommonCPP/Regexp/Regexp.h"
#include "../CommonCPP/StringUtils/StringUtils.h"

bool SubUtils::hourToMilliseconds_srt(const std::string& timestr, unsigned int& out) {
    std::string pattern_srt = "(\\d+):(\\d+):(\\d+),(\\d+)$";
    int totalMatchingGroups = StringUtils::charCount(pattern_srt, '(');
    std::vector<std::string> vdata;
    Regexp::search(timestr, pattern_srt, vdata);

    if (vdata.size() == totalMatchingGroups) {  // Parse successful
        int h, m, s, ms;
        StringUtils::StringToInteger(vdata.at(0), h);
        StringUtils::StringToInteger(vdata.at(1), m);
        StringUtils::StringToInteger(vdata.at(2), s);
        StringUtils::StringToInteger(vdata.at(3), ms);
        out += h * 3600000;
        out += m * 60000;
        out += s * 1000;
        out += ms;
        return true;
    } else {                                    // Parse failed
        return false;
    }
}

bool SubUtils::hourToMilliseconds_ass(const std::string& timestr, unsigned int& out) {
    std::string pattern_ass = "(\\d+):(\\d+):(\\d+)\\.(\\d+)";
    int totalMatchingGroups = StringUtils::charCount(pattern_ass, '(');
    std::vector<std::string> vdata;
    Regexp::search(timestr, pattern_ass, vdata);

    if (vdata.size() == totalMatchingGroups) {  // Parse successful
        int h, m, s, ms;
        StringUtils::StringToInteger(vdata.at(0), h);
        StringUtils::StringToInteger(vdata.at(1), m);
        StringUtils::StringToInteger(vdata.at(2), s);
        StringUtils::StringToInteger(vdata.at(3), ms);
        out += h * 3600000;
        out += m * 60000;
        out += s * 1000;
        out += ms;
        return true;
    } else {                                    // Parse failed
        return false;
    }
}

bool SubUtils::hourToMilliseconds(const std::string& timestr, unsigned int& out) {
    out = 0;

    if (hourToMilliseconds_srt(timestr, out) == true) {
        return true;
    } else if (hourToMilliseconds_ass(timestr, out) == true) {
        return true;
    } else {
        // Parse failed, timestr did not match any pattern
        return false;
    }
}