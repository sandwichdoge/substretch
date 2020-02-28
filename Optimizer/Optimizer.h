#ifndef INCLUDE_OPTIMIZER_H
#define INCLUDE_OPTIMIZER_H
#include <string>
#include <vector>
#include "../SubLine/SubLine.h"
#include "../SubLine/SubLine_srt/SubLine_srt.h"
#include "../SubLine/SubLine_ass/SubLine_ass.h"

enum OPTIMIZING_PARAM {OPTIMIZING_PARAM_STRETCH_TIME = 1, OPTIMIZING_PARAM_MERGE_LINES = 2};

class Optimizer {
    public:
        Optimizer(std::vector<SubLine> *data, enum SUB_TYPE subType);
        virtual ~Optimizer();

        int optimize(int whatdo);
    private:
        std::vector<SubLine> _data;
        std::vector<SubLine_srt>* _data_srt;
        std::vector<SubLine_ass>* _data_ass;
        enum SUB_TYPE _subType;
        int stretchTime();
        int mergeShortLines();
};
#endif
