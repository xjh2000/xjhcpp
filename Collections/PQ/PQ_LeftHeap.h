#pragma once
#pragma once

#include <tuple>

#include "../PQ/PQ.h" //引入优先级队列ADT
#include "../BinTree/BinTree.h" //引入二叉树节点模板类

/**
 * \brief 优先级队列的左式堆归并算法
 * \tparam T collection elem
 * \param a collection
 * \param b collection
 * \return merge collection
 * \note complexity O(log(max(a.size(), b.size())))
 */
template <typename T> //根据相对优先级确定适宜的方式，合并以a和b为根节点的两个左式堆
static BinNodePosi<T> merge(BinNodePosi<T> a, BinNodePosi<T> b)
{
    if (!a) return b;
    if (!b) return a;
    if (a->data < b->data) std::swap(a, b);
    a->rc = merge(a->rc, b);
    a->rc->parent = a;
    if (!a->lc || a->lc->npl < a->rc->npl)std::swap(a->lc, a->rc);
    a->npl = a->rc ? a->rc->npl + 1 : 1;
    return a;
}


template <typename T>
class PQ_LeftHeap : public PQ<T>, public BinTree<T>
{
public:
    PQ_LeftHeap()
    {
    } //默认构造
    PQ_LeftHeap(T* E, int n) //批量构造：可改进为Floyd建堆算法
    {
        for (int i = 0; i < n; i++) insert(E[i]);
    }

    void insert(T) override; //按照比较器确定的优先级次序插入元素
    T getMax() override; //取出优先级最高的元素
    T delMax() override; //删除优先级最高的元素
}; //PQ_LeftHeap


template <typename T>
void PQ_LeftHeap<T>::insert(T e)
{
    this->_root = merge(this->_root, new BinNode<T>(e, nullptr));
    ++this->_size;
}

template <typename T>
T PQ_LeftHeap<T>::getMax()
{
    return this->_root->data;
}

template <typename T>
T PQ_LeftHeap<T>::delMax()
{
    BinNodePosi<T> lHeap = this->_root->lc;
    BinNodePosi<T> rHeap = this->_root->rc;
    T e = this->_root->data;
    delete this->_root;
    this->_root = merge(lHeap, rHeap);
    if (this->_root)this->_root->parent = nullptr;
    return e;
}
