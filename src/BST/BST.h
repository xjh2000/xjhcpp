//
// Created by xjh on 2/19/2022.
//

#pragma once

#include "BinTree/BinTree.h" //引入BinTree

template<typename T>
class BST : public BinTree<T> { //由BinTree派生BST模板类
protected:
    BinNodePosi<T> _hot; //“命中”节点的父亲

//    BinNodePosi<T> connect34 ( //按照“3 + 4”结构，联接3个节点及四棵子树
//            BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>,
//            BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T>, BinNodePosi<T> );

    BinNodePosi<T> rotateAt(BinNodePosi<T> x); //对x及其父亲、祖父做统一旋转调整

    BinNodePosi<T> &searchIN(BinNodePosi<T> v, const T &e);

    BinNodePosi<T> removeAt(BinNodePosi<T> x);

public: //基本接口：以virtual修饰，强制要求所有派生类（BST变种）根据各自的规则对其重写

    virtual BinNodePosi<T> &search(const T &e); //查找

    virtual BinNodePosi<T> insert(const T &e); //插入

    virtual bool remove(const T &e); //删除

    /*DSA*/
//    void stretchToLPath() { stretchByZag ( _root ); } //借助zag旋转，转化为左向单链
//    void stretchToRPath() { stretchByZig ( _root ); } //借助zig旋转，转化为右向单链
//    void stretch();
};

template<typename T>
BinNodePosi<T> &BST<T>::search(const T &e) {
    _hot = NULL;
    return searchIN(this->root(), e);
}

template<typename T>
BinNodePosi<T> &BST<T>::searchIN(BinNodePosi<T> v, const T &e) {
    if (!v || v->data == e) {
        return v;
    }
    _hot = v;
    return searchIN((v->data < e ? v->rc : v->lc), e);
}

template<typename T>
BinNodePosi<T> BST<T>::insert(const T &e) {
    BinNodePosi<T> x = search(e);
    if (x) return x;
    x = new BinNode<T>(e, _hot);
    if (!_hot) {
        this->_root = x;
    } else if (_hot->data < e) {
        _hot->rc = x;
    } else
        _hot->lc = x;
    this->_size++;
    this->updateHeightAbove(x);
    return x;
}

template<typename T>
bool BST<T>::remove(const T &e) {
    BinNodePosi<T> x = search(e);
    if (!x) return false;
    removeAt(x);
    this->_size--;
    this->updateHeightAbove(_hot);
    return true;
}

template<typename T>
BinNodePosi<T> BST<T>::removeAt(BinNodePosi<T> x) {
    BinNodePosi<T> w = x;
    BinNodePosi<T> succ = NULL;
    BinNodePosi<T> u = x->parent;
    if (!HasLChild(*x)) {
        ((u->lc == x) ? u->lc : u->rc) = succ = x->rc;
    } else if (!HasRChild(*x)) {
        ((u->lc == x) ? u->lc : u->rc) = succ = x->lc;
    } else {
        w = x->succ();
        std::swap(x->data, w->data);
        u = w->parent;
        ((u == x) ? u->rc : u->lc) = succ = w->rc;
    }
    _hot = w->parent;
    if (succ) succ->parent = _hot;
    delete w;
    return succ;
}

template<typename T>
BinNodePosi<T> BST<T>::rotateAt(BinNodePosi<T> x) {
    return nullptr;
}

