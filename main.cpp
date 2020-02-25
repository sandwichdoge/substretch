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
    int rc = pParser->parse(target);
    if (rc != 0) {  // Parsing failure
        return -2;
    }

    std::list<SubLine>* data = pParser->getParsedData();
    std::cout << "Found " << data->size() << " lines\n";

    enum SUB_TYPE subType = pParser->getParsedSubtype();
    switch (subType) {
        case (SUB_TYPE_ASS): {
            std::list<SubLine_ass>* list = (std::list<SubLine_ass>*)data;
            for (auto it : *list) {
                std::cout << it.text << ":";
                std::cout << it.start_time << ":";
                std::cout << it.style << "\n";
            }
            break;
        }
        case (SUB_TYPE_SRT): {
            std::list<SubLine_srt>* list = (std::list<SubLine_srt>*)data;
            for (auto it : *list) {
                std::cout << it.index << ":";
                std::cout << it.text << ":";
                std::cout << it.start_time << "\n";
            }
            break;
        }
    }

    
    delete pParser;
    return 0;
}