//
// Created by xjh on 3/20/2022.
//

#include <random>
#include "gtest/gtest.h"

class Dictionary : public testing::Test {
public:

    std::uniform_int_distribution<int> dist;
    std::default_random_engine e;

    Dictionary() {
        // 以随机值播种，若可能
        std::random_device r;
        // 选择 1 与 10000 间的随机数
        std::default_random_engine e1(r());
        e = e1;
        std::uniform_int_distribution<int> uniform_dist(1, 10000);
        dist = uniform_dist;
    }

};

TEST_F(Dictionary, base) {

    printf("BST base pass");
}