#include "gtest/gtest.h"
#include "../SubUtils/SubUtils.h"
#include "../SubLine/SubLine.h"
#include <iostream>

TEST(SubUtils, hourToMilliseconds_ass) {
    unsigned int out = 0;
    bool success = SubUtils::hourToMilliseconds("0:02:40.65", out, SUB_TYPE_ASS);
    EXPECT_EQ(success, true);
    EXPECT_EQ(out, 160065);
    std::cout << out << "\n";
}

TEST(SubUtils, hourToMilliseconds_srt) {
    unsigned int out = 0;
    bool success = SubUtils::hourToMilliseconds("00:00:04,200", out, SUB_TYPE_SRT);
    EXPECT_EQ(success, true);
    EXPECT_EQ(out, 4200);
    std::cout << out << "\n";
}

TEST(SubUtils, millisecondsToHour_ass) {
    std::string out_ass;
    SubUtils::millisecondsToHour(1000, out_ass, SUB_TYPE_ASS);
    std::cout << out_ass << "\n";
    EXPECT_EQ(out_ass, "00:00:01.00");
}

TEST(SubUtils, millisecondsToHour_srt) {
    std::string out_ass;
    SubUtils::millisecondsToHour(1000, out_ass, SUB_TYPE_SRT);
    std::cout << out_ass << "\n";
    EXPECT_EQ(out_ass, "00:00:01,000");
}