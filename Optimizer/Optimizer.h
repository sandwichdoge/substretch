#ifndef INCLUDE_OPTIMIZER_H
#define INCLUDE_OPTIMIZER_H
#include <string>
#include <list>
#include "../SubLine/SubLine.h"
#include "../SubLine/SubLine_srt/SubLine_srt.h"
#include "../SubLine/SubLine_ass/SubLine_ass.h"

enum OPTIMIZING_PARAM {OPTIMIZING_PARAM_STRETCH_TIME = 1, OPTIMIZING_PARAM_MERGE_LINES = 2};

class Optimizer {
    public:
        Optimizer(std::list<SubLine> *data, enum SUB_TYPE subType);
        virtual ~Optimizer();

        int optimize(int whatdo);
    private:
        std::list<SubLine> *_data;
        enum SUB_TYPE _subType;
        int stretchTime();
        int mergeShortLines();
};
#endif
