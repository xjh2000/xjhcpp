//
// Created by xjh on 3/24/2022.
//

#pragma once

#define  Parent(i)         ( ( ( i ) - 1 ) >> 1 ) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]的左孩子
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]的右孩子
#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //判断PQ[i]是否合法
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //判断PQ[i]是否有两个孩子
#define  Bigger(PQ, i, j)  ( lt( PQ[i], PQ[j] ) ? j : i ) //取大者（等时前者优先）
#define  ProperParent(PQ, n, i) /*父子（至多）三者中的大者*/ \
            ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
            ) \
            ) //相等时父节点优先，如此可避免不必要的交换

#include "Vector/Vector.h" //借助多重继承机制，基于向量
#include "PQ.h" //按照优先级队列ADT实现的

//template<typename T>
//struct PQ_ComplHeap : public PQ<T>, public Vector<T> { //完全二叉堆
//    /*DSA*/friend class UniPrint; //演示输出使用，否则不必设置友类
//    PQ_ComplHeap() {} //默认构造
//    PQ_ComplHeap(T *A, Rank n) {
//        copyFrom(A, 0, n);
//        heapify(_elem, n);
//    } //批量构造
//    void insert(T); //按照比较器确定的优先级次序，插入词条
//    T getMax(); //读取优先级最高的词条
//    T delMax(); //删除优先级最高的词条
//}; //PQ_ComplHeap
//template <typename T> void heapify ( T* A, Rank n ); //Floyd建堆算法
//template <typename T> Rank percolateDown ( T* A, Rank n, Rank i ); //下滤
//template <typename T> Rank percolateUp ( T* A, Rank i ); //上滤
