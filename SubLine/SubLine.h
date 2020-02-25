#ifndef INCLUDE_SUBLINE_H
#define INCLUDE_SUBLINE_H
#include <string>

class SubLine {
    public:
        SubLine();
        virtual ~SubLine();

        std::string text;
        unsigned int start_time; // In milliseconds
        unsigned int end_time;   // In milliseconds
};
#endif
