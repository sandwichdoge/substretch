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

    std::cout << "Parsing..\n";
    Parser *pParser = new Parser();
    int rc = pParser->parse(target);
    if (rc != 0) {  // Parsing failure
        return -2;
    }

    std::vector<SubLine>* data = pParser->getParsedData();
    enum SUB_TYPE subType = pParser->getParsedSubtype();

    std::cout << "Optimizing..\n";
    Optimizer *pOptimizer = new Optimizer(data, subType);
    pOptimizer->optimize(OPTIMIZING_PARAM_MERGE_LINES | OPTIMIZING_PARAM_STRETCH_TIME);
    std::vector<SubLine>* optimized = pOptimizer->getOptimizedSub();

    // Apply optimized timing to original data
    for (std::size_t i = 0; i < optimized->size(); i++) {
        std::cout << i << "\n";
        //data->at(i).start_time = optimized->at(i).start_time;
        //data->at(i).end_time = optimized->at(i).end_time;
        //data->at(i).text = optimized->at(i).text;
        std::cout << data->at(i).text << " = " << optimized->at(i).text << "\n";
    }
    //data->resize(optimized->size());

    delete pOptimizer;
    delete pParser;
    return 0;
}