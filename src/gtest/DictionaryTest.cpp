//
// Created by xjh on 3/20/2022.
//

#include <random>
#include "gtest/gtest.h"
#include "Dictionary/SkipList.h"

class DictionaryTest : public testing::Test {
public:

    std::uniform_int_distribution<int> dist;
    std::default_random_engine e;

    DictionaryTest() {
        // 以随机值播种，若可能
        std::random_device r;
        // 选择 1 与 10000 间的随机数
        std::default_random_engine e1(r());
        e = e1;
        std::uniform_int_distribution<int> uniform_dist(1, 10000);
        dist = uniform_dist;
    }

};

TEST_F(DictionaryTest, quadlist) {
    Quadlist<int> quadlist;
    quadlist.insertAfterAbove(20, quadlist.first()->pred);
    quadlist.insertAfterAbove(30, quadlist.first());
    EXPECT_EQ(quadlist.last()->entry, 30);
    EXPECT_EQ(quadlist.first()->entry, 20);

    printf("quadlist  pass");
}


TEST_F(DictionaryTest, SkipList) {
    Skiplist<std::string, int> skiplist;
    skiplist.put("haoGe", 20);
    skiplist.put("jim", 30);
    ASSERT_EQ(*skiplist.get("haoGe"), 20);
    ASSERT_EQ(*skiplist.get("jim"), 30);
    skiplist.remove("jim");
    ASSERT_EQ(skiplist.get("jim"), nullptr);
    printf("SkipList  pass");
}