#include "Optimizer.h"
#include "../SubUtils/SubUtils.h"
#include <iostream>
#include <vector>

#define DEFAULT_MS_PER_WORD 500

Optimizer::Optimizer() {
    _configs.stretchTime_msPerWord = DEFAULT_MS_PER_WORD; 
}

Optimizer::~Optimizer() {}

int Optimizer::optimize(std::vector<SubLine> *data, enum SUB_TYPE subType, int whatdo) {
    if (!_data_ass || !_data_srt) {
        return -1;      // Null data
    }

    switch (subType) {
        case (SUB_TYPE_SRT):
            _data = std::vector<SubLine>(((std::vector<SubLine_srt>*)data)->begin(), ((std::vector<SubLine_srt>*)data)->end());
            _data_srt = (std::vector<SubLine_srt>*)data;
            break;
        case (SUB_TYPE_ASS):
            _data = std::vector<SubLine>(((std::vector<SubLine_ass>*)data)->begin(), ((std::vector<SubLine_ass>*)data)->end());
            _data_ass = (std::vector<SubLine_ass>*)data;
            break;
        default:
            return -2;  // Unsupported sub type
    }

    if (_data.size() == 0) {
        return -3;      // Empty sub    
    }

    _subType = subType;

    if (whatdo & OPTIMIZING_PARAM_STRETCH_TIME) {
        stretchTime();
    }

    if (whatdo & OPTIMIZING_PARAM_MERGE_LINES) {
        mergeShortLines();
    }

    finish();           // Apply optimized timing to original data
    return 0;
}

int Optimizer::finish() {
    switch (_subType) {
        case (SUB_TYPE_ASS):
            for (std::size_t i = 0; i < _data.size(); i++) {
                _data_ass->at(i).start_time = _data.at(i).start_time;
                _data_ass->at(i).end_time = _data.at(i).end_time;
                _data_ass->at(i).text = _data.at(i).text;
            }
            _data_ass->resize(_data.size());
            break;
        case (SUB_TYPE_SRT):
            for (std::size_t i = 0; i < _data.size(); i++) {
                _data_srt->at(i).start_time = _data.at(i).start_time;
                _data_srt->at(i).end_time = _data.at(i).end_time;
                _data_srt->at(i).text = _data.at(i).text;
            }
            _data_srt->resize(_data.size());
            break;
        default:
            return -3;
    }

    return 0;
}

int Optimizer::stretchTime() {
    for (std::size_t i = 0; i < _data.size() - 1; i++) { // No need to stretch last line
        int totalWords = SubUtils::countWords(_data.at(i).text);
        unsigned int nextStart = _data.at(i + 1).start_time;

        unsigned int currentStart = _data.at(i).start_time;
        unsigned int newDuration = totalWords * _configs.stretchTime_msPerWord; // Milliseconds        
        unsigned int newEnd = currentStart + newDuration;

        // If new duration exceeds next line's start_time, cut new end_time to next line's start_time.
        if (newEnd >= nextStart) {
            newEnd = nextStart - 50;
        }

        unsigned int currentDuration = _data.at(i).end_time - _data.at(i).start_time;
        if (newDuration > currentDuration) {
            _data.at(i).end_time = newEnd;
        }
    }

    return 0;
}

int Optimizer::mergeShortLines() {
    return 0;
}

void Optimizer::setConfig(const struct OptimizerConfigs& configs) {
    _configs = configs;
}