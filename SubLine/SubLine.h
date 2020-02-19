#ifndef INCLUDE_SUBLINE_H
#define INCLUDE_SUBLINE_H
#include <string>

class SubLine {
    public:
        SubLine(const std::string& raw);
        virtual ~SubLine();

        std::string content;
        int start_time; // In milliseconds
        int end_time;   // In milliseconds
};
#endif
