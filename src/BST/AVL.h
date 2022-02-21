//
// Created by xjh on 2/21/2022.
//

#pragma once

#include "BST.h" //基于BST实现AVL树

/******************************************************************************************
 * 在左、右孩子中取更高者
 * 在AVL平衡调整前，借此确定重构方案
 ******************************************************************************************/
#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*左高*/ \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*右高*/ \
   IsLChild( * (x) ) ? (x)->lc : (x)->rc /*等高：与父亲x同侧者（zIg-zIg或zAg-zAg）优先*/ \
   ) \
   ) \
)


template<typename T>
class AVL : public BST<T> { //由BST派生AVL树模板类
public:
    BinNodePosi<T> insert(const T &e); //插入（重写）
//    bool remove(const T &e); //删除（重写）
// BST::search()等其余接口可直接沿用
};

template<typename T>
BinNodePosi<T> AVL<T>::insert(const T &e) {
    BinNodePosi<T> x = this->search(e);
    if (x) return x;

    BinNodePosi<T> xx = x = new BinNode<T>(e, this->_hot);
    if (!this->_hot) {
        this->_root = x;
    } else if (this->_hot->data < e) {
        this->_hot->rc = x;
    } else
        this->_hot->lc = x;
    this->_size++;
    this->updateHeight(this->_hot);

    for (BinNodePosi<T> g = this->_hot; g; g = g->parent) {
        if (!AvlBalanced(*g)) {
            FromParentTo(*g) = this->rotateAt(tallerChild(tallerChild(g)));
            break;
        } else {
            this->updateHeight(g);
        }
    }

    return xx;
}
