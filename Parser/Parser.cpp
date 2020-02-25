#include "Parser.h"
#include "../CommonCPP/Regexp/Regexp.h"
#include "../CommonCPP/FileUtils/FileUtils.h"
#include "../CommonCPP/StringUtils/StringUtils.h"
#include "../SubLine/SubLine_ass/SubLine_ass.h"
#include "../SubLine/SubLine_srt/SubLine_srt.h"
#include "../SubUtils/SubUtils.h"

#include <iostream>
#include <vector>

#define ASS_FILE_COLUMN_COUNT 10

Parser::Parser() {
    _totalLines = 0;
    _isDataReady = false;
}

Parser::~Parser() {
}

int Parser::parse(const std::string& subtitleFilePath) {
    int ret = 0;
    _subType = detectSubtype(subtitleFilePath);
    _totalLines = countLines(subtitleFilePath);

    switch (_subType) {
        case SUB_TYPE_ASS: {
            ret = parse_ass(subtitleFilePath, _data);
            break;
        }
        case SUB_TYPE_SRT: {
            ret = parse_srt(subtitleFilePath, _data);
            break;
        }
        case SUB_TYPE_UNKNOWN: {
            ret = -1;
            break;
        }
    }

    if (ret == 0) _isDataReady = true;

    return ret;
}

int Parser::parse_ass(const std::string& subtitleFilePath, std::list<SubLine>& out) {
    // https://www.regextester.com/104838
    std::string pattern = "(?:^|\n)Dialogue:\\s(.*\\d+),(\\d+:\\d+:\\d+\\.\\d+),(\\d+:\\d+:\\d+\\.\\d+),([\\w\\s]+),(\\w*),(\\d+),(\\d+),(\\d+),(\\w*),(.*)";
    std::string data;
    int rc = FileUtils::readFile(subtitleFilePath, data);
    std::vector<std::string> vdata;

    if (rc == 0) {
        Regexp::search(data, pattern, vdata);

        if (vdata.size() % 10 != 0) {
            // Handle error: regex parsing failure
            std::cout << "Regex parsing error\n";
        }

        for (size_t i = 0; i < vdata.size(); i+= ASS_FILE_COLUMN_COUNT) {
            // TODO parse "Format" row to see which column stands for which instead of hardcode
            SubLine_ass *sub = new SubLine_ass;

            SubUtils::hourToMilliseconds(vdata.at(i + 1), sub->start_time);
            SubUtils::hourToMilliseconds(vdata.at(i + 2), sub->end_time);
            sub->style = vdata.at(i + 3);
            sub->name  = vdata.at(i + 4);
            StringUtils::StringToInteger(vdata.at(i + 5), sub->marginL);
            StringUtils::StringToInteger(vdata.at(i + 6), sub->marginR);
            StringUtils::StringToInteger(vdata.at(i + 7), sub->marginV);
            sub->effect = vdata.at(i + 8);
            sub->text   = vdata.at(i + 9);

            out.push_back(*sub);
            delete sub;
        }
    }

    return 0;
}

int Parser::parse_srt(const std::string& subtitleFilePath, std::list<SubLine>& out) {
    std::string pattern = "(\\d+)\\n([\\d:,]+)\\s+-{2}\\>\\s+([\\d:,]+)\\n([\\s\\S]*?(?=\\n{2}|$))";
    std::string data;
    int rc = FileUtils::readFile(subtitleFilePath, data);
    std::vector<std::string> vdata;

    if (rc == 0) {
        Regexp::search(data, pattern, vdata);
        for (int i = 0; i < vdata.size(); i++) {
            std::cout << i << "--" << vdata.at(i) << "\n";
        }
    }
    
    return 0;
}



enum SUB_TYPE Parser::detectSubtype(const std::string& subtitleFilePath) {
    std::size_t pos = subtitleFilePath.rfind(".");
    std::string fileExt; // File extension, including the period (.txt)
    if (pos != std::string::npos) {
        fileExt = subtitleFilePath.substr(pos, subtitleFilePath.length() - pos);
    }

    enum SUB_TYPE ret;

    if (fileExt == ".ass") {
        ret = SUB_TYPE_ASS;
    } else if (fileExt == ".srt") {
        ret = SUB_TYPE_SRT;
    } else {
        ret = SUB_TYPE_UNKNOWN;
    }

    return ret;
}

int Parser::countLines(const std::string& subtitleFilePath) {
    int ret = 0;

    for (size_t i = 0; i < subtitleFilePath.length(); i++) {
        if (subtitleFilePath[i] == '\n') {
            ret++;
        }
    }

    return ret;
}

std::list<SubLine> Parser::getParsedData() {
    return _data;
}

enum SUB_TYPE Parser::getParsedSubtype() {
    return _subType;
}
