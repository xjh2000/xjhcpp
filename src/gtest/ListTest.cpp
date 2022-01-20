#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by xjh on 1/18/2022.
//

#include <random>
#include "gtest/gtest.h"
#include "ListNode.h"
#include "List.h"

namespace {
    class ListTest : public testing::Test {
    public:

        std::uniform_int_distribution<int> dist;
        std::default_random_engine e;

        ListTest() {
            // 以随机值播种，若可能
            std::random_device r;
            // 选择 1 与 6 间的随机数
            std::default_random_engine e1(r());
            e = e1;
            std::uniform_int_distribution<int> uniform_dist(1, 10000);
            dist = uniform_dist;
        }
    };

    TEST_F(ListTest, ListNode) {
        ListNode<int> head{};
        ListNode<int> tail{};
        head.succ = &tail;
        tail.pred = &head;
        head.insertAsSucc(10);
        tail.insertAsPred(30);
        ASSERT_EQ(head.succ->data, 10);
        ASSERT_EQ(head.succ->succ->data, 30);
        ASSERT_EQ(tail.pred->data, 30);
        ASSERT_EQ(tail.pred->pred->data, 10);
        printf("ListNode pass");
    }

    TEST_F(ListTest, BaseOperate) {
        List<int> list;
        list.insertAsFirst(10);
        list.insertAsLast(40);
        ASSERT_EQ(list[0], 10);
        ASSERT_EQ(list[1], 40);
        list.insert(list.first(), 20);
        list.insert(30, list.last());
        ASSERT_EQ(list[1], 20);
        ASSERT_EQ(list[2], 30);
        List<int> list1(list);
        ASSERT_EQ(list1[0], 10);
        ASSERT_EQ(list1.size(), 4);
        List<int> list2(list, 1, 3);
        ASSERT_EQ(list2[0], 20);
        ASSERT_EQ(list2.size(), 3);
        List<int> list3(list.first(), 2);
        ASSERT_EQ(list3[1], 20);
        ASSERT_EQ(list3.size(), 2);

        printf("BaseOperate pass");
    }

    TEST_F(ListTest, Deduplication) {
        List<int> list;
        for (int i = 0; i < 100; ++i) {
            list.insertAsLast(i);
            list.insertAsLast(i);
            list.insertAsLast(i);
        }
        ASSERT_EQ(list.deduplicate(), 200);
        ASSERT_EQ(list[0], 0);
        ASSERT_EQ(list[50], 50);
        ASSERT_EQ(list[99], 99);
        printf("Deduplication pass");
    }

    TEST_F(ListTest, Uniquify) {
        List<int> list;
        for (int i = 0; i < 100; ++i) {
            list.insertAsLast(i);
            list.insertAsLast(i);
            list.insertAsLast(i);
        }
        ASSERT_EQ(list.uniquify(), 200);
        ASSERT_EQ(list[0], 0);
        ASSERT_EQ(list[50], 50);
        ASSERT_EQ(list[99], 99);
        printf("uniquify pass");
    }

    TEST_F(ListTest, Reverse) {
        List<int> list;
        for (int i = 0; i < 100; ++i) list.insertAsLast(i);
        list.reverse();
        ASSERT_EQ(list[0], 99);
        ASSERT_EQ(list[50], 49);
        ASSERT_EQ(list[99], 0);
        printf("Reverse pass");
    }

    TEST_F(ListTest, Traverse) {
        List<int> list;
        for (int i = 0; i < 100; ++i) list.insertAsLast(i);
        list.traverse([&](ListNodePosi<int> node) { node->data++; });
        ASSERT_EQ(list[0], 1);
        ASSERT_EQ(list[50], 51);
        ASSERT_EQ(list[99], 100);
        printf("Traverse pass");
    }

    TEST_F(ListTest, Search) {
        List<int> list;
        for (int i = 0; i < 100; ++i) list.insertAsLast(i);
        ASSERT_EQ(list.search(0)->data, 0);
        ASSERT_EQ(list.search(50)->data, 50);
        ASSERT_EQ(list.search(99)->data, 99);
        printf("Search pass");
    }

    TEST_F(ListTest, SelectMax) {
        List<int> list;
        for (int i = 0; i < 100; ++i) list.insertAsLast(i);
        ASSERT_EQ(list.selectMax()->data, 99);
        printf("SelectMax pass");
    }

    TEST_F(ListTest, InsertionSort) {
        List<int> list;
        for (int i = 0; i < 100; ++i) list.insertAsFirst(i);
        list.insertionSort(list.first(), list.size());
        for (int i = 0; i < 100; ++i) {
            ASSERT_EQ(list[i], i);
        }
        printf("InsertionSort pass");
    }
}
#pragma clang diagnostic pop