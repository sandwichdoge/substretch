#include <iostream>
#include <list>
#include <fstream>
#include "Parser/Parser.h"

int main(int argc, char* argv[])
{
    std::string target;

    if (argc >= 2) {
        target = std::string(argv[1]);
    } else {
        return -1;
    }

    Parser *pParser = new Parser();
    pParser->parse(target);

    std::list<SubLine> data = pParser->getParsedData();
    std::cout << "Found " << data.size() << " lines\n";
    
    delete pParser;
    return 0;
}