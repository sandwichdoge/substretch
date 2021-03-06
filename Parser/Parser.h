#ifndef INCLUDE_PARSER_H
#define INCLUDE_PARSER_H
#include <string>
#include <vector>
#include "../SubLine/SubLine.h"
#include "../SubLine/SubLine_srt/SubLine_srt.h"
#include "../SubLine/SubLine_ass/SubLine_ass.h"

class Parser {
    public:
        Parser();
        virtual ~Parser();
        // Parse subtitle file into a list of detailed subtitle lines
        int parse(const std::string& subtitleFilePath);
        enum SUB_TYPE getParsedSubtype();
        // Need to cast returned point to appropriate type.
        std::vector<SubLine>* getParsedData();
    private:
        enum SUB_TYPE detectSubtype(const std::string& subtitleFilePath);
        int parse_ass();
        int parse_srt();

        std::string _raw;
        std::vector<SubLine>* _data;
        std::vector<SubLine_srt> _data_srt;
        std::vector<SubLine_ass> _data_ass;
        enum SUB_TYPE _subType;
        bool _isDataReady;
};
#endif
