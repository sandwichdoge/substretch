#include "Optimizer.h"
#include "../SubUtils/SubUtils.h"
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
        // Lengthen end_time, if end_time exceed next sub's start_time, cut it at next sub's start_time.
        // 0.4s per word.
        int wordCount = SubUtils::countWords(it.text);
        int newDuration = wordCount * 400; // In milliseconds.
        
    }
}

int Optimizer::mergeShortLines() {
    
}