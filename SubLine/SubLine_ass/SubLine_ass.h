#ifndef INCLUDE_SUBLIME_ASS_H
#define INCLUDE_SUBLIME_ASS_H
#include <string>
#include "../SubLine.h"

class SubLine_ass : public SubLine {
    public:
        SubLine_ass();
        virtual ~SubLine_ass();

        std::string marked;
        std::string layer;
        std::string style;
        std::string name;
        int marginL;
        int marginR;
        int marginV;
        std::string effect;
};
#endif
