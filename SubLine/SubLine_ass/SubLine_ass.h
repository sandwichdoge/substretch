#include <string>
#include "../SubLine.h"

class SubLine_ass : public SubLine {
    public:
        SubLine_ass(const std::string& raw);
        virtual ~SubLine_ass();

        std::string layer;
        int start_time; // In milliseconds
        int end_time;   // In milliseconds
        std::string style;
        std::string name;
        int marginL;
        int marginR;
        int marginV;
        std::string effect;
        std::string content;
};