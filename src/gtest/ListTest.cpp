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
}
#pragma clang diagnostic pop