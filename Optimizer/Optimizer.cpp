#include "Optimizer.h"
#include <iostream>

Optimizer::Optimizer() {}
Optimizer::~Optimizer() {}

int Optimizer::optimize(std::list<SubLine> *data, enum SUB_TYPE subType) {
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

    return 0;
}