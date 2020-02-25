#ifndef INCLUDE_SUBLINE_H
#define INCLUDE_SUBLINE_H
#include <string>

enum SUB_TYPE {SUB_TYPE_UNKNOWN = 0, SUB_TYPE_SRT, SUB_TYPE_ASS};

class SubLine {
    public:
        SubLine();
        virtual ~SubLine();

        enum SUB_TYPE subType;
        std::string text;
        unsigned int start_time; // In milliseconds
        unsigned int end_time;   // In milliseconds
};
#endif
