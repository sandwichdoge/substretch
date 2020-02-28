#include "Builder.h"
#include "../SubUtils/SubUtils.h"
#include "../CommonCPP/StringUtils/StringUtils.h"
#include <iostream>

Builder::Builder() {}
Builder::~Builder() {}

int Builder::build(std::vector<SubLine> *data, enum SUB_TYPE subType) {
    int ret = 0;
    _subType = subType;

    switch (subType) {
        case (SUB_TYPE_SRT): {
            std::vector<SubLine_srt> *tmp = (std::vector<SubLine_srt> *)data;
            ret = build_srt(tmp);
            break;
        }
        case (SUB_TYPE_ASS): {
            std::vector<SubLine_ass> *tmp = (std::vector<SubLine_ass> *)data;
            ret = build_ass(tmp);
            break;
        }
        default:
            ret = -1;
            break;
    }

    return ret;
}

int Builder::build_srt(std::vector<SubLine_srt> *data) {
    std::string fmt_start; // Formated time
    std::string fmt_end; // Formated time

    for (std::size_t i = 0; i < data->size(); i++) {
        SubUtils::millisecondsToHour(data->at(i).start_time, fmt_start, _subType);
        SubUtils::millisecondsToHour(data->at(i).end_time, fmt_end, _subType);

        std::string sentence;
        sentence += StringUtils::intToString(data->at(i).index);
        sentence += '\n';
        sentence += fmt_start;
        sentence += " --> ";
        sentence += fmt_end;
        sentence += '\n';
        sentence += data->at(i).text;
        sentence += '\n';

        _raw += sentence;
    }

    return 0;
}

int Builder::build_ass(std::vector<SubLine_ass> *data) {
    return 0;
}