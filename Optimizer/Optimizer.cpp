#include "Optimizer.h"
#include <iostream>

Optimizer::Optimizer(std::list<SubLine> *data, enum SUB_TYPE subType) {
    _data = data;
    _subType = subType;
}

Optimizer::~Optimizer() {}

int Optimizer::optimize(int whatdo) {
    if (whatdo & OPTIMIZING_PARAM_STRETCH_TIME) {
        stretchTime();
    }

    if (whatdo & OPTIMIZING_PARAM_MERGE_LINES) {
        mergeShortLines();
    }

    return 0;
}

int Optimizer::stretchTime() {
    for (auto it : *_data) {
        std::cout << it.text << "\n";
    }
}

int Optimizer::mergeShortLines() {
    
}