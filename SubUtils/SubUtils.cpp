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

bool SubUtils::hourToMilliseconds(const std::string& timestr, unsigned int& out, enum SUB_TYPE subType) {
    out = 0;

    switch (subType) {
        case (SUB_TYPE_ASS):
            return hourToMilliseconds_ass(timestr, out);
        case (SUB_TYPE_SRT):
            return hourToMilliseconds_srt(timestr, out);
        default:
            return false;
    }
}

int SubUtils::countWords(const std::string& sentence) {
    int totalSpace = StringUtils::charCount(sentence, ' ');
    int totalLinebreaks = StringUtils::charCount(sentence, '\n');

    return totalLinebreaks + totalSpace + 1;
}

int SubUtils::CRLFtoLF(std::string& str) {
    StringUtils::stringReplace(str, "\r\n", "\n");

    return 0;
}

bool SubUtils::millisecondsToHour(unsigned int ms, std::string& out, enum SUB_TYPE subType) {
    int remain = 0;
    int h = ms / 3600000;
    remain = ms % 3600000;
    int m = remain / 60000;
    remain = remain % 60000;
    int s = remain / 1000;
    int ms_carry = ms % 1000;

    std::string h_s = StringUtils::intToString(h);
    std::string m_s = StringUtils::intToString(m);
    std::string s_s = StringUtils::intToString(s);
    std::string ms_s = StringUtils::intToString(ms_carry);

    h_s = zeroPrefix(h_s, 2);
    m_s = zeroPrefix(m_s, 2);
    s_s = zeroPrefix(s_s, 2);
    ms_s = zeroPrefix(ms_s, 3);

    switch (subType) {
        case (SUB_TYPE_ASS):
            // 01:02:40.65
            ms_s = ms_s.substr(0, 2);
            out = h_s + ':' + m_s + ':' + s_s + '.' + ms_s;
            break;
        case (SUB_TYPE_SRT):
            // 02:10:01,600
            out = h_s + ':' + m_s + ':' + s_s + ',' + ms_s;
            break;
        default:
            return false;
    }

    return true;
}

std::string SubUtils::zeroPrefix(const std::string& num, int maxlen) {
    std::string ret = num;
    for (int i = 0; i < maxlen; i++) {
        ret = '0' + ret;
    }

    ret = StringUtils::stringRight(ret, maxlen);
    return ret;
}