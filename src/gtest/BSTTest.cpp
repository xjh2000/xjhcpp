//
// Created by xjh on 2/19/2022.
//

#include <random>
#include "gtest/gtest.h"
#include "BST/BST.h"
#include "BST/AVL.h"

class BSTTest : public testing::Test {
public:

    std::uniform_int_distribution<int> dist;
    std::default_random_engine e;

    BSTTest() {
        // 以随机值播种，若可能
        std::random_device r;
        // 选择 1 与 10000 间的随机数
        std::default_random_engine e1(r());
        e = e1;
        std::uniform_int_distribution<int> uniform_dist(1, 10000);
        dist = uniform_dist;
    }

};

TEST_F(BSTTest, base) {
    BST<int> tree;
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    EXPECT_EQ(tree.search(40)->data, 40);
    EXPECT_EQ(tree.remove(40), true);
    EXPECT_EQ(tree.search(44), nullptr);
    printf("BST base pass");
}


TEST_F(BSTTest, AVL) {
    AVL<int> tree;
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    EXPECT_EQ(tree.search(40)->data, 40);
    EXPECT_EQ(tree.remove(40), true);
    EXPECT_EQ(tree.remove(30), true);
    EXPECT_EQ(tree.search(44), nullptr);
    printf("BST AVL pass");
}
