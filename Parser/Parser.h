#include <string>
#include <list>
#include "../SubLine/SubLine.h"

enum SUB_TYPE {SUB_TYPE_UNKNOWN = 0, SUB_TYPE_SRT, SUB_TYPE_ASS};

class Parser {
    public:
        // Parse subtitle file into a list of detailed subtitle lines
        int parse(const std::string& subtitleFilePath, enum SUB_TYPE subType, std::list<SubLine>& out);
};
