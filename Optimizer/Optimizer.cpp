#include "Optimizer.h"
#include "../SubUtils/SubUtils.h"
#include <iostream>
#include <vector>

Optimizer::Optimizer(std::vector<SubLine> *data, enum SUB_TYPE subType) {
    switch (subType) {
        case (SUB_TYPE_SRT):
            _data = std::vector<SubLine>(((std::vector<SubLine_srt>*)data)->begin(), ((std::vector<SubLine_srt>*)data)->end());
            break;
        case (SUB_TYPE_ASS):
            _data = std::vector<SubLine>(((std::vector<SubLine_ass>*)data)->begin(), ((std::vector<SubLine_ass>*)data)->end());
            break;
        default:
            break;
    }
    
    _subType = subType;
}

Optimizer::~Optimizer() {}

int Optimizer::optimize(int whatdo) {
    if (_data.size() == 0) {
        return -1;  // Empty sub
    }

    if (whatdo & OPTIMIZING_PARAM_STRETCH_TIME) {
        stretchTime();
    }

    if (whatdo & OPTIMIZING_PARAM_MERGE_LINES) {
        mergeShortLines();
    }

    return 0;
}

int Optimizer::stretchTime() {
    for (size_t i = 0; i < _data.size(); i++) {
        std::cout << _data.at(i).text << "\n";
    }
    return 0;
}

int Optimizer::mergeShortLines() {
    return 0;
}