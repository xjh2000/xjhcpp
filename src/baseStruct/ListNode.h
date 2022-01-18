//
// Created by xjh on 1/18/2022.
//

#pragma once

using Rank = int; //秩
template<typename T>
struct ListNode;
template<typename T> using ListNodePosi = ListNode<T> *; //列表节点位置
template<typename T>
struct ListNode { //列表节点模板类（以双向链表形式实现）
// 成员
    T data;
    ListNodePosi<T> pred;
    ListNodePosi<T> succ; //数值、前驱、后继
// 构造函数
    ListNode() = default; //针对header和trailer的构造
    explicit ListNode(T e, ListNodePosi<T> p = 0, ListNodePosi<T> s = 0)
            : data(e), pred(p), succ(s) {} //默认构造器
// 操作接口
    ListNodePosi<T> insertAsPred(T const &e); //紧靠当前节点之前插入新节点
    ListNodePosi<T> insertAsSucc(T const &e); //紧随当前节点之后插入新节点
};

template<typename T>
ListNodePosi<T> ListNode<T>::insertAsPred(const T &e) {
    auto x = new ListNode(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

template<typename T>
ListNodePosi<T> ListNode<T>::insertAsSucc(const T &e) {
    auto x = new ListNode(e, this,succ );
    succ->pred = x;
    succ = x;
    return x;
}


