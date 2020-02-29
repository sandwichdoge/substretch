#ifndef INCLUDE_OPTIMIZER_H
#define INCLUDE_OPTIMIZER_H
#include <string>
#include <vector>
#include "../SubLine/SubLine.h"
#include "../SubLine/SubLine_srt/SubLine_srt.h"
#include "../SubLine/SubLine_ass/SubLine_ass.h"

enum OPTIMIZING_PARAM {OPTIMIZING_PARAM_STRETCH_TIME = 1, OPTIMIZING_PARAM_MERGE_LINES = 2};

struct OptimizerConfigs {
    unsigned int stretchTime_msPerWord;

};

class Optimizer {
    public:
        Optimizer();
        virtual ~Optimizer();

        void setConfig(const struct OptimizerConfigs& configs);
        int optimize(std::vector<SubLine> *data, enum SUB_TYPE subType, int whatdo);
    private:
        struct OptimizerConfigs _configs;
        std::vector<SubLine> _data;
        std::vector<SubLine_srt>* _data_srt;
        std::vector<SubLine_ass>* _data_ass;
        enum SUB_TYPE _subType;
        int stretchTime();
        int mergeShortLines();
        // Update original data with optimized data
        int finish();
};
#endif
