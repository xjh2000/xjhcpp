//
// Created by xjh on 3/20/2022.
//
#pragma once

#include "../Entry/Entry.h"

template <typename T>
struct QuadlistNode;
template <typename T>
using QListNodePosi = QuadlistNode<T>*; //跳转表节点位置
template <typename T>
struct QuadlistNode
{
    //QuadlistNode模板类
    T entry; //所存词条
    QListNodePosi<T> pred;
    QListNodePosi<T> succ; //前驱、后继
    QListNodePosi<T> above;
    QListNodePosi<T> below; //上邻、下邻
    explicit QuadlistNode //构造器
    (T e = T(), QListNodePosi<T> p = nullptr, QListNodePosi<T> s = nullptr,
     QListNodePosi<T> a = nullptr, QListNodePosi<T> b = nullptr)
        : entry(e), pred(p), succ(s), above(a), below(b)
    {
    }

    QListNodePosi<T> insertAsSuccAbove //插入新节点，以当前节点为前驱，以节点b为下邻
    (const T& e, QListNodePosi<T> b = nullptr);
};

template <typename T>
QListNodePosi<T> QuadlistNode<T>::insertAsSuccAbove(const T& e, QListNodePosi<T> b)
{
    QListNodePosi<T> newNode = new QuadlistNode(e, this, this->succ, nullptr, b);
    this->succ->pred = newNode;
    this->succ = newNode;
    if (b) b->above = newNode;
    return newNode;
}
