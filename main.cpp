#include <iostream>
#include <list>
#include <fstream>
#include "Parser/Parser.h"
#include "Optimizer/Optimizer.h"
#include "Builder/Builder.h"
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

    // Parse input file
    Parser *pParser = new Parser();
    int rc = pParser->parse(target);
    if (rc != 0) {  // Parsing failure
        return -2;
    }

    std::vector<SubLine>* data = pParser->getParsedData();
    enum SUB_TYPE subType = pParser->getParsedSubtype();

    // Optimize parsed subtitle
    Optimizer *pOptimizer = new Optimizer();
    struct OptimizerConfigs conf = {.stretchTime_msPerWord = 400};
    pOptimizer->setConfig(conf);
    pOptimizer->optimize(data, subType, OPTIMIZING_PARAM_MERGE_LINES | OPTIMIZING_PARAM_STRETCH_TIME);

    // Rebuild optimized subtitle
    Builder* pBuilder = new Builder();
    pBuilder->build(data, subType);
    std::string raw = pBuilder->getResult();

    // Print final result to stdout
    std::cout << raw << "\n";

    // Clean up
    delete pBuilder;
    delete pOptimizer;
    delete pParser;
    return 0;
}