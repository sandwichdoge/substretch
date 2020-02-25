#ifndef INCLUDE_PARSER_H
#define INCLUDE_PARSER_H
#include <string>
#include <list>
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
        std::list<SubLine>* getParsedData();
    private:
        enum SUB_TYPE detectSubtype(const std::string& subtitleFilePath);
        int parse_ass(const std::string& subtitleFilePath);
        int parse_srt(const std::string& subtitleFilePath);

        std::string _raw;
        std::list<SubLine>* _data;
        std::list<SubLine_srt> _data_srt;
        std::list<SubLine_ass> _data_ass;
        enum SUB_TYPE _subType;
        bool _isDataReady;
};
#endif
