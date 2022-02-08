//
// Created by xjh on 1/27/2022.
//

#include "gtest/gtest.h"
#include "GraphMatrix.h"

namespace {
    class GraphTest : public testing::Test {
    };

    TEST_F(GraphTest, bfs) {
        GraphMatrix<int, int> graph;
        for (int i = 0; i < 6; ++i) {
            graph.insert(i);
        }
        graph.insert(0, 0, 0, 1);
        graph.insert(0, 0, 0, 2);
        graph.insert(0, 0, 1, 2);
        graph.insert(0, 0, 1, 3);
        graph.insert(0, 0, 1, 4);
        graph.insert(0, 0, 4, 2);
        graph.insert(0, 0, 4, 5);
        graph.bfs(0);
        auto list = graph.traversalOrder();
        ASSERT_EQ(list[0], 0);
        ASSERT_EQ(list[1], 2);
        ASSERT_EQ(list[2], 1);
        ASSERT_EQ(list[3], 4);
        ASSERT_EQ(list[4], 3);
        ASSERT_EQ(list[5], 5);
        printf("bfs pass");
    }

    TEST_F(GraphTest, dfs) {
        GraphMatrix<int, int> graph;
        for (int i = 0; i < 6; ++i) {
            graph.insert(i);
        }
        graph.insert(0, 0, 0, 1);
        graph.insert(0, 0, 0, 2);
        graph.insert(0, 0, 1, 2);
        graph.insert(0, 0, 1, 3);
        graph.insert(0, 0, 1, 4);
        graph.insert(0, 0, 4, 2);
        graph.insert(0, 0, 4, 5);
        graph.dfs(0);
        auto list = graph.traversalOrder();
        ASSERT_EQ(list[0], 0);
        ASSERT_EQ(list[1], 2);
        ASSERT_EQ(list[2], 1);
        ASSERT_EQ(list[3], 4);
        ASSERT_EQ(list[4], 5);
        ASSERT_EQ(list[5], 3);
        printf("dfs pass");
    }

    TEST_F(GraphTest, tSort) {
        GraphMatrix<int, int> graph;
        for (int i = 0; i < 6; ++i) {
            graph.insert(i);
        }
        graph.insert(0, 0, 0, 2);
        graph.insert(0, 0, 1, 2);
        graph.insert(0, 0, 1, 5);
        graph.insert(0, 0, 2, 5);
        graph.insert(0, 0, 2, 3);
        graph.insert(0, 0, 2, 4);
        graph.insert(0, 0, 4, 5);
        auto list = graph.tSort(1);
        for (int i = 0; i < list.size(); ++i) {
            ASSERT_EQ(list.size() - i - 1, list[i]);
        }
        printf("tSort pass");
    }

}