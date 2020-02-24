#ifndef INCLUDE_SUBLIME_SRT_H
#define INCLUDE_SUBLIME_SRT_H
#include <string>
#include "../SubLine.h"

class SubLine_srt : public SubLine {
    public:
        SubLine_srt();
        virtual ~SubLine_srt();

        int index;
};
#endif
