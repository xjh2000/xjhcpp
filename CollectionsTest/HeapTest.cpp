//
// Created by xjh on 3/20/2022.
//

#include <random>
#include "gtest/gtest.h"
#include "../Collections/Dictionary/SkipList.h"
#include "../Collections/PQ/PQ_ComplHeap.h"
#include "../Collections/PQ/PQ_LeftHeap.h"

class HeapTest : public testing::Test
{
public:
    std::uniform_int_distribution<int> dist;
    std::default_random_engine e;

    HeapTest()
    {
        // 以随机值播种，若可能
        std::random_device r;
        // 选择 1 与 10000 间的随机数
        std::default_random_engine e1(r());
        e = e1;
        std::uniform_int_distribution<int> uniform_dist(1, 10000);
        dist = uniform_dist;
    }
};

TEST_F(HeapTest, ComplateHeap)
{
    pq_compl_heap<int> heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(30);
    heap.insert(-1);
    EXPECT_EQ(heap.getMax(), 30);
    heap.delMax();
    EXPECT_EQ(heap.getMax(), 20);
    int intArray[] =
    {
        10, 20, 5, 30, -1
    };
    pq_compl_heap<int> heap1(intArray, 5);
    EXPECT_EQ(heap1.getMax(), 30);
    heap1.delMax();
    EXPECT_EQ(heap1.getMax(), 20);
    printf("ComplateHeap  pass");
}

TEST_F(HeapTest, LeftHeap)
{
    PQ_LeftHeap<int> heap;
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(30);
    heap.insert(-1);
    EXPECT_EQ(heap.getMax(), 30);
    heap.delMax();
    EXPECT_EQ(heap.getMax(), 20);
    int intArray[] =
    {
        10, 20, 5, 30, -1
    };
    PQ_LeftHeap<int> heap1(intArray, 5);
    EXPECT_EQ(heap1.getMax(), 30);
    heap1.delMax();
    EXPECT_EQ(heap1.getMax(), 20);
    printf("LeftHeap  pass");
}
