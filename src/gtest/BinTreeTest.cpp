//
// Created by xjh on 1/23/2022.
//
#include <random>
#include "gtest/gtest.h"
#include "BinTree.h"

namespace {
    class BinTreeTest : public testing::Test {
    public:

        std::uniform_int_distribution<int> dist;
        std::default_random_engine e;

        BinTreeTest() {
            // 以随机值播种，若可能
            std::random_device r;
            // 选择 1 与 6 间的随机数
            std::default_random_engine e1(r());
            e = e1;
            std::uniform_int_distribution<int> uniform_dist(1, 10000);
            dist = uniform_dist;
        }
    };

    TEST_F(BinTreeTest, BinNodeBase) {
        BinNode<int> node(10);
        node.insertAsRC(20);
        node.insertAsLC(5);
        ASSERT_EQ(5, node.lc->data);
        ASSERT_EQ(20, node.rc->data);
        printf("BinNodeBase pass");
    }

    TEST_F(BinTreeTest, Insert) {
        BinTree<int> tree;
        tree.insert(20);
        tree.insert(tree.root(), 30);
        tree.insert(10, tree.root());
        ASSERT_EQ(tree.root()->data, 20);
        ASSERT_EQ(tree.root()->lc->data, 10);
        ASSERT_EQ(tree.root()->rc->data, 30);
        ASSERT_EQ(tree.root()->height, 1);
        ASSERT_EQ(tree.size(), 3);
        printf("Insert pass");
    }

    TEST_F(BinTreeTest, Attach) {
        BinTree<int> tree;
        tree.insert(20);
        BinTree<int> tree1;
        tree1.insert(10);
        BinTree<int> tree2;
        tree2.insert(30);
        tree.attach(tree1, tree.root());
        tree.attach(tree.root(), tree2);

        ASSERT_EQ(tree.root()->data, 20);
        ASSERT_EQ(tree.root()->lc->data, 10);
        ASSERT_EQ(tree.root()->rc->data, 30);
        ASSERT_EQ(tree.root()->height, 1);
        ASSERT_EQ(tree.size(), 3);

        printf("Attach pass");
    }


}
