//
// Created by 93462 on 1/12/2022.
//

#include "gtest/gtest.h"
#include "Vector.h"

namespace {

    class VectorTest : public testing::Test {
    };

    TEST_F(VectorTest, based_operation) {
        Vector<int> v;
        for (int i = 0; i < 100; ++i) v.insert(i);
        ASSERT_EQ(v[0], 0);
        ASSERT_EQ(v[50], 50);
        ASSERT_EQ(v[99], 99);
        v.insert(50, 100);
        ASSERT_EQ(v[50], 100);
        ASSERT_THROW(v[-1], std::out_of_range);
        ASSERT_THROW(v[101], std::out_of_range);
        ASSERT_EQ(v.remove(0), 0);
        ASSERT_EQ(v.remove(0, 60), 60);
        ASSERT_EQ(v[0], 60);

        v.traverse([&](int &elem) { elem++; });
        ASSERT_EQ(v[0], 61);
        v.unsort();

        printf("based_operation pass");
    }

    TEST_F(VectorTest, search) {
        Vector<int> v;
        for (int i = 0; i < 100; ++i) v.insert(i);
        int r = v.find(50);
        ASSERT_EQ(r, 50);
        r = v.find(100);
        ASSERT_EQ(r, -1);
        r = v.find(-1);
        ASSERT_EQ(r, -1);
        v.binSearch(50);
        ASSERT_EQ(v.binSearch(50), 50);
        ASSERT_EQ(v.binSearch(100), 99);
        ASSERT_EQ(v.binSearch(-1), -1);

        printf("search pass");
    }

    TEST_F(VectorTest, deduplication) {
        Vector<int> v;
        for (int i = 0; i < 100; ++i) {
            v.insert(i);
            v.insert(i);
            v.insert(i);
        }
        v.deduplicate();
        for (int i = 0; i < 100; ++i) {
            ASSERT_EQ(v[i], i);
        }
        Vector<int> v1;
        for (int i = 0; i < 100; ++i) {
            v1.insert(i);
            v1.insert(i);
            v1.insert(i);
        }
        v = v1;
        v.uniquify();
        for (int i = 0; i < 100; ++i) {
            ASSERT_EQ(v[i], i);
        }
        Vector<int> v2;
        for (int i = 0; i < 100; ++i) {
            v2.insert(i);
            v2.insert(i);
            v2.insert(i);
        }
        v = v2;
        v.uniquify1();
        for (int i = 0; i < 100; ++i) {
            ASSERT_EQ(v[i], i);
        }
        printf("deduplication pass");
    }


}
