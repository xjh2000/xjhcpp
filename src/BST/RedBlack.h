//
// Created by xjh on 3/3/2022.
//

#pragma once

#include "BST.h" //基于BST实现RedBlack

template<typename T>
class RedBlack : public BST<T> { //RedBlack树模板类
protected:

    void solveDoubleRed(BinNodePosi<T> x); //双红修正

//    void solveDoubleBlack ( BinNodePosi<T> x ); //双黑修正

    int updateHeight(BinNodePosi<T> x); //更新节点x的高度

public:
    BinNodePosi<T> insert(const T &e); //插入（重写）

//    bool remove ( const T& e ); //删除（重写）

// BST::search()等其余接口可直接沿用
};

template<typename T>
int RedBlack<T>::updateHeight(BinNodePosi<T> x) {
    return x->height = IsBlack(x) + std::max(stature(x->lc), stature(x->rc));
}

template<typename T>
BinNodePosi<T> RedBlack<T>::insert(const T &e) {
    auto x = this->search(e);
    if (x) return x;
    x = new BinNode<T>(e, this->_hot, nullptr, nullptr, -1);
    this->_size++;
    solveDoubleRed(x);
    return x ? x : this->_hot->parent;
}

template<typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi<T> x) {

}
