#ifndef INCLUDE_BUILDER_H
#define INCLUDE_BUILDER_H
#include "../SubLine/SubLine.h"
#include <vector>

class Builder {
public:
    Builder();
    virtual ~Builder();

    int build(std::vector<SubLine> *data);
};

#endif