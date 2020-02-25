#include <iostream>
#include <list>
#include <fstream>
#include "Parser/Parser.h"
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
    pParser->parse(target);

    std::list<SubLine>* data = pParser->getParsedData();
    std::cout << "Found " << data->size() << " lines\n";

    if (pParser->getParsedSubtype() == SUB_TYPE_ASS) {
        std::list<SubLine_ass>* list = (std::list<SubLine_ass>*)data;
        for (auto it : *list) {
            std::cout << it.text << "\n";
            std::cout << it.start_time << "\n";
        }
    }

    
    delete pParser;
    return 0;
}