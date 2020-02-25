#ifndef INCLUDE_OPTIMIZER_H
#define INCLUDE_OPTIMIZER_H
#include <string>
#include <list>
#include "../SubLine/SubLine.h"
#include "../SubLine/SubLine_srt/SubLine_srt.h"
#include "../SubLine/SubLine_ass/SubLine_ass.h"

class Optimizer {
    public:
        Optimizer();
        virtual ~Optimizer();

        int optimize(std::list<SubLine> *data, enum SUB_TYPE subType);
    private:
        int n;
};
#endif
