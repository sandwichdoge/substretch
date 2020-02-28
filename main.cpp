#include <iostream>
#include <list>
#include <fstream>
#include "Parser/Parser.h"
#include "Optimizer/Optimizer.h"
#include "SubLine/SubLine.h"
#include "SubLine/SubLine_ass/SubLine_ass.h"
#include "SubLine/SubLine_srt/SubLine_srt.h"

int main(int argc, char* argv[])
{
    std::string target;

    if (argc >= 2) {
        target = std::string(argv[1]);
    } else {
        return -1;
    }

    Parser *pParser = new Parser();
    int rc = pParser->parse(target);
    if (rc != 0) {  // Parsing failure
        return -2;
    }

    std::vector<SubLine>* data = pParser->getParsedData();
    enum SUB_TYPE subType = pParser->getParsedSubtype();

    std::cout << data->size() << "\n";

    Optimizer *pOptimizer = new Optimizer(data, subType);
    pOptimizer->optimize(OPTIMIZING_PARAM_MERGE_LINES | OPTIMIZING_PARAM_STRETCH_TIME);


    delete pOptimizer;
    delete pParser;
    return 0;
}