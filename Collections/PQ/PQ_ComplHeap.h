//
// Created by xjh on 3/24/2022.
//

// ReSharper disable CppClangTidyClangDiagnosticUnusedMacros
#pragma once

#include <stack>

#include "../Vector/Vector.h" //借助多重继承机制，基于向量
#include "PQ.h" //按照优先级队列ADT实现的

#define  Parent(i)         ( ( ( i ) - 1 ) >> 1 ) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define  ParentValid(i)   ((i) > 0)
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]的左孩子
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]的右孩子
#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //判断PQ[i]是否合法
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //判断PQ[i]是否有两个孩子
#define  Bigger(PQ, i, j)  ( ( (PQ)[i] < (PQ)[j] ) ? (j) : (i) ) //取大者（等时前者优先）
#define  ProperParent(PQ, n, i)  \
( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : (i) \
) \
) //相等时父节点优先，如此可避免不必要的交换


template <typename T>
void heapify(T* A, Rank n); //Floyd建堆算法

template <typename T>
Rank percolate_down(T* A, Rank n, Rank i); //下滤

template <typename T>
Rank percolate_up(T* A, Rank i)
{
    Rank father;
    while (
        ParentValid(i) &&
        A[i] > A[father = Parent(i)])
    {
        std::swap(A[i], A[father]);
        i = father;
    }
    return i;
}

//上滤

template <typename T>
struct pq_compl_heap : public PQ<T>, public Vector<T>
{
    //完全二叉堆
    pq_compl_heap() = default;

    pq_compl_heap(T* A, Rank n)
    {
        this->copyFrom(A, 0, n);
        heapify(this->_elem, n);
    }


    // ReSharper disable once CppHidingFunction
    void insert(T) override; //按照比较器确定的优先级次序，插入词条
    T getMax() override; //读取优先级最高的词条
    T delMax() override; //删除优先级最高的词条
}; //PQ_ComplHeap

template <typename T>
void heapify(T* A, Rank n)
{
    for (int i = n / 2 - 1; 0 <= i; i--)
        percolate_down(A, n, i);
}

template <typename T>
Rank percolate_down(T* A, Rank n, Rank i)
{
    Rank j;
    while (i != (j = ProperParent(A, n, i)))
    {
        std::swap(A[i], A[j]);
        i = j;
    }
    return i;
}

template <typename T>
void pq_compl_heap<T>::insert(T e)
{
    Vector<T>::insert(e);
    percolate_up(this->_elem, this->_size - 1);
}


template <typename T>
T pq_compl_heap<T>::getMax()
{
    return this->_elem[0];
}

template <typename T>
T pq_compl_heap<T>::delMax()
{
    if (this->_size == 0)
    {
        return reinterpret_cast<T>(nullptr);
    }
    T max_elem = this->_elem[0];
    auto size = this->_size - 1 > 0 ? this->_size - 1 : 0;
    this->_elem[0] = this->_elem[size];
    this->remove(size);
    percolate_down(this->_elem, size, 0);
    return max_elem;
}
