//
// Created by 93462 on 2022/1/8.
//

#include <gtest/gtest.h>
#include "Hello.h"


// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
// Expect two strings not to be equal.
    EXPECT_STREQ(Hello().sayhello().c_str(), "Hello, world");
}