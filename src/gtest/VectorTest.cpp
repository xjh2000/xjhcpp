//
// Created by 93462 on 1/12/2022.
//

#include "gtest/gtest.h"
#include "Vector.h"


namespace {

    class VectorTest : public testing::Test {
    };

    TEST_F(VectorTest, initialized) {
        Vector<int> v;
        for (int i = 0; i < 100; ++i) v.insert(i);
        ASSERT_EQ(v[0], 0);
        ASSERT_EQ(v[50], 50);
        ASSERT_EQ(v[99], 99);
        v.insert(50, 100);
        ASSERT_EQ(v[50], 100);
        ASSERT_THROW(v[-1], std::out_of_range);
        ASSERT_THROW(v[101], std::out_of_range);
        v.unsort();
        printf("ok");
    }

}
