#ifndef INCLUDE_BUILDER_H
#define INCLUDE_BUILDER_H
#include "../SubLine/SubLine.h"
#include "../SubLine/SubLine_ass/SubLine_ass.h"
#include "../SubLine/SubLine_srt/SubLine_srt.h"
#include <vector>

class Builder {
public:
    Builder();
    virtual ~Builder();

    int build(std::vector<SubLine> *data, enum SUB_TYPE subType);
    std::string getResult() {return _raw;}
private:
    int build_srt(std::vector<SubLine_srt> *data);
    int build_ass(std::vector<SubLine_ass> *data);

    std::string _raw;
    enum SUB_TYPE _subType;
};

#endif