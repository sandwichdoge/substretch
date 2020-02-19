#include <iostream>
#include <list>
#include <fstream>
#include "Parser/Parser.h"

int main()
{
    Parser *pParser = new Parser();
    //pParser->parse();
    
    delete pParser;

    std::cout << "It works!\n";
    return 0;
}