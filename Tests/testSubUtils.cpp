#include "gtest/gtest.h"
#include "../SubUtils/SubUtils.h"
#include <iostream>

TEST(SubUtils, hourToMilliseconds_ass) {
    unsigned int out = 0;
    bool success = SubUtils::hourToMilliseconds("0:02:40.65", out);
    EXPECT_EQ(success, true);
    EXPECT_EQ(out, 160065);
    std::cout << out << "\n";
}

TEST(SubUtils, hourToMilliseconds_srt) {
    unsigned int out = 0;
    bool success = SubUtils::hourToMilliseconds("00:00:04,200", out);
    EXPECT_EQ(success, true);
    EXPECT_EQ(out, 4200);
    std::cout << out << "\n";
}