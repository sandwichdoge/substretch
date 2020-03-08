#include <iostream>
#include <list>
#include <fstream>
#include <unistd.h>
#include <stdio.h>  
#include "Parser/Parser.h"
#include "Optimizer/Optimizer.h"
#include "Builder/Builder.h"
#include "SubLine/SubLine.h"
#include "SubLine/SubLine_ass/SubLine_ass.h"
#include "SubLine/SubLine_srt/SubLine_srt.h"
#include "StringUtils/StringUtils.h"

void show_help() {
    printf("-w <milliseconds>\t\tHow many milliseconds per word to stretch a sentence.\n"
    "-i <SubtileFile>\t\tPath to input subtitle file.\n"
    "-h\t\t\t\tShow help.\n\n"
    "Example: ./substretch.out -i film.srt -w 500\n");
}

int main(int argc, char* argv[])
{
    std::string target;
    int msPerWord = 400;

    // Process cmdline arguments
    if (argc < 2) {
        show_help();
        return -1;
    }

    int opt;
    while((opt = getopt(argc, argv, "i:w:h")) != -1) {
        switch (opt) {
            case 'i': {
                target = std::string(argv[optind - 1]);
                break;
            }
            case 'w': {
                StringUtils::StringToInteger(std::string(argv[optind - 1]), msPerWord);
                break;
            }
            case 'h': {
                show_help();
                return 0;
            }
        }
    }

    // Validate cmdline arguments
    if (target.empty()) {
        std::cout << "No target file specified.\n";
        return -2;
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
    struct OptimizerConfigs conf = {.stretchTime_msPerWord = (unsigned int)msPerWord};
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