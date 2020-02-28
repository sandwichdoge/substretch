#include "Parser.h"
#include "../CommonCPP/Regexp/Regexp.h"
#include "../CommonCPP/FileUtils/FileUtils.h"
#include "../CommonCPP/StringUtils/StringUtils.h"
#include "../SubLine/SubLine_ass/SubLine_ass.h"
#include "../SubLine/SubLine_srt/SubLine_srt.h"
#include "../SubUtils/SubUtils.h"

#include <iostream>
#include <vector>

#define TOTAL_SUB_FIELDS_ASS 10
#define TOTAL_SUB_FIELDS_SRT 4

Parser::Parser() {
    _isDataReady = false;
}

Parser::~Parser() {
}

int Parser::parse(const std::string& subtitleFilePath) {
    int ret = 0;
    _subType = detectSubtype(subtitleFilePath);
    int rc = FileUtils::readFile(subtitleFilePath, _raw);
    SubUtils::CRLFtoLF(_raw);

    if (rc == 0) {
        switch (_subType) {
            case SUB_TYPE_ASS: {
                ret = parse_ass();
                _data = (std::vector<SubLine>*)&_data_ass;
                break;
            }
            case SUB_TYPE_SRT: {
                ret = parse_srt();
                _data = (std::vector<SubLine>*)&_data_srt;
                break;
            }
            case SUB_TYPE_UNKNOWN: {
                ret = -1;
                break;
            }
        }
    } else {        // Failed to read file.
        std::cout << "Error: File read failed[" << subtitleFilePath << "]\n";
        ret = -1;
    }

    if (ret == 0) _isDataReady = true;

    return ret;
}

int Parser::parse_ass() {
    // https://www.regextester.com/104838
    std::string pattern = "(?:^|\n)Dialogue:\\s(.*\\d+),(\\d+:\\d+:\\d+\\.\\d+),(\\d+:\\d+:\\d+\\.\\d+),([\\w\\s]+),(\\w*),(\\d+),(\\d+),(\\d+),(\\w*),(.*)";
    std::vector<std::string> vdata;
    Regexp::search(_raw, pattern, vdata);

    if (vdata.size() % TOTAL_SUB_FIELDS_ASS != 0) {
        // Handle error: regex parsing failure
        std::cout << "Regex parsing error\n";
    }

    for (size_t i = 0; i < vdata.size(); i+= TOTAL_SUB_FIELDS_ASS) {
        // TODO parse "Format" row to see which column stands for which instead of hardcode
        SubLine_ass *sub = new SubLine_ass;

        sub->subType = SUB_TYPE_ASS;
        sub->marked = vdata.at(i);
        SubUtils::hourToMilliseconds(vdata.at(i + 1), sub->start_time, SUB_TYPE_ASS);
        SubUtils::hourToMilliseconds(vdata.at(i + 2), sub->end_time, SUB_TYPE_ASS);
        sub->style  = vdata.at(i + 3);
        sub->name   = vdata.at(i + 4);
        StringUtils::StringToInteger(vdata.at(i + 5), sub->marginL);
        StringUtils::StringToInteger(vdata.at(i + 6), sub->marginR);
        StringUtils::StringToInteger(vdata.at(i + 7), sub->marginV);
        sub->effect = vdata.at(i + 8);
        sub->text   = vdata.at(i + 9);

        _data_ass.push_back(*sub);
        delete sub;
    }


    return 0;
}

int Parser::parse_srt() {
    std::string pattern = "(\\d+)\\n([\\d:,]+)\\s+-{2}\\>\\s+([\\d:,]+)\\n([\\s\\S]*?(?=\\n{2}|$))";
    std::vector<std::string> vdata;
    Regexp::search(_raw, pattern, vdata);

    if (vdata.size() % TOTAL_SUB_FIELDS_SRT != 0) {
        // Handle error: regex parsing failure
        std::cout << "Regex parsing error\n";
    }

    for (size_t i = 0; i < vdata.size(); i+= TOTAL_SUB_FIELDS_SRT) {
        SubLine_srt *sub = new SubLine_srt;

        sub->subType = SUB_TYPE_SRT;
        StringUtils::StringToInteger(vdata.at(i + 0), sub->index);
        SubUtils::hourToMilliseconds(vdata.at(i + 1), sub->start_time, SUB_TYPE_SRT);
        SubUtils::hourToMilliseconds(vdata.at(i + 2), sub->end_time, SUB_TYPE_SRT);
        sub->text = vdata.at(i + 3);

        _data_srt.push_back(*sub);
        delete sub;
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

std::vector<SubLine>* Parser::getParsedData() {
    return _data;
}

enum SUB_TYPE Parser::getParsedSubtype() {
    return _subType;
}
