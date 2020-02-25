#include "gtest/gtest.h"
#include "../SubUtils/SubUtils.h"
#include <iostream>

TEST(SubUtils, hourToMilliseconds) {
    unsigned int out = 0;
    bool success = SubUtils::hourToMilliseconds("0:02:40.65", out);
    EXPECT_EQ(success, true);
    EXPECT_EQ(out, 160065);
    std::cout << out << "\n";
}