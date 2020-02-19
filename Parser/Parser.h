#ifndef INCLUDE_PARSER_H
#define INCLUDE_PARSER_H
#include <string>
#include <list>
#include "../SubLine/SubLine.h"

enum SUB_TYPE {SUB_TYPE_UNKNOWN = 0, SUB_TYPE_SRT, SUB_TYPE_ASS};

class Parser {
    public:
        Parser();
        virtual ~Parser();
        // Parse subtitle file into a list of detailed subtitle lines
        int parse(const std::string& subtitleFilePath);
        enum SUB_TYPE getParsedSubtype();
        std::list<SubLine> getParsedData();
    private:
        enum SUB_TYPE detectSubtype(const std::string& subtitleFilePath);
        int countLines(const std::string& subtitleFilePath);
        int parse_ass(const std::string& subtitleFilePath, std::list<SubLine>& out);
        //parse_srt(const std::string& subtitleFilePath);

        std::list<SubLine> _data;
        int _totalLines;
        enum SUB_TYPE _subType;
        bool _isDataReady;
};
#endif
