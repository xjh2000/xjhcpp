//
// Created by xjh on 2/23/2022.
//

#pragma once

#include "BST.h"

template<typename NodePosi>
inline //在节点*p与*lc（可能为空）之间建立父（左）子关系
void attachAsLC(NodePosi lc, NodePosi p) {
    p->lc = lc;
    if (lc) lc->parent = p;
}

template<typename NodePosi>
inline //在节点*p与*rc（可能为空）之间建立父（右）子关系
void attachAsRC(NodePosi p, NodePosi rc) {
    p->rc = rc;
    if (rc) rc->parent = p;
}

template<typename T>
class Splay : public BST<T> {
protected:
    BinNodePosi<T> splay(BinNodePosi<T> v);

public:
    BinNodePosi<T> &search(const T &e) override;

    bool remove(const T &e) override;

    BinNodePosi<T> insert(const T &e) override;
};

template<typename T>
BinNodePosi<T> Splay<T>::splay(BinNodePosi<T> v) {
    if (!v) return nullptr;
    BinNodePosi<T> p;
    BinNodePosi<T> g;
    while ((p = v->parent) && (g = p->parent)) { //自下而上，反复对*v做双层伸展
        BinNodePosi<T> gg = g->parent; //每轮之后*v都以原曾祖父（great-grand parent）为父
        if (IsLChild (*v))
            if (IsLChild (*p)) { //zig-zig
                attachAsLC(p->rc, g);
                attachAsLC(v->rc, p);
                attachAsRC(p, g);
                attachAsRC(v, p);
            } else { //zig-zag
                attachAsLC(v->rc, p);
                attachAsRC(g, v->lc);
                attachAsLC(g, v);
                attachAsRC(v, p);
            }
        else if (IsRChild (*p)) { //zag-zag
            attachAsRC(g, p->lc);
            attachAsRC(p, v->lc);
            attachAsLC(g, p);
            attachAsLC(p, v);
        } else { //zag-zig
            attachAsRC(p, v->lc);
            attachAsLC(v->rc, g);
            attachAsRC(v, g);
            attachAsLC(p, v);
        }
        if (!gg) v->parent = nullptr; //若*v原先的曾祖父*gg不存在，则*v现在应为树根
        else //否则，*gg此后应该以*v作为左或右孩子
            (g == gg->lc) ? attachAsLC(v, gg) : attachAsRC(gg, v);
        this->updateHeight(g);
        this->updateHeight(p);
        this->updateHeight(v);
    } //双层伸展结束时，必有g == NULL，但p可能非空
    if ((p = v->parent)) { //若p果真非空，则额外再做一次单旋
        if (IsLChild (*v)) {
            attachAsLC(v->rc, p);
            attachAsRC(v, p);
        } else {
            attachAsRC(p, v->lc);
            attachAsLC(p, v);
        }
        this->updateHeight(p);
        this->updateHeight(v);
    }
    v->parent = nullptr;
    return v;
}

template<typename T>
BinNodePosi<T> &Splay<T>::search(const T &e) {
    this->_hot = nullptr;
    BinNodePosi<T> p = this->searchIN(this->_root, e);
    this->_root = splay(p ? p : this->_hot);
    return this->_root;
}

template<typename T>
BinNodePosi<T> Splay<T>::insert(const T &e) {
    if (!this->_root) {
        this->_size++;
        return this->_root = new BinNode<T>(e);
    }
    if (e == search(e)->data) return this->_root;
    this->_size++;
    BinNodePosi<T> t = this->_root;
    if (t->data > e) {
        t->parent = this->_root = new BinNode<T>(e, nullptr, nullptr, t);
        if (t->lc && t->lc->data < e) {
            this->_root->lc = t->lc;
            t->lc->parent = this->_root;
            t->lc = nullptr;
        }
    } else {
        t->parent = this->_root = new BinNode<T>(e, nullptr, t, nullptr);
        if (t->rc && t->rc->data > e) {
            this->_root->rc = t->rc;
            t->rc->parent = this->_root;
            t->rc = nullptr;
        }
    }
    this->updateHeightAbove(t);
    return this->_root;
}

template<typename T>
bool Splay<T>::remove(const T &e) {
    if (!this->_root || e != search(e)->data) return false;
    BinNodePosi<T> w = this->_root;
    if (!HasLChild(*w)) {
        this->_root = this->_root->rc;
        if (this->_root) {
            this->_root->parent = nullptr;
        }
    } else if (!HasRChild(*w)) {
        this->_root = this->_root->lc;
        if (this->_root) {
            this->_root->parent = nullptr;
        }
    } else {
        this->_root = w->lc;
        this->_root->parent = nullptr;
        search(e);
        this->_root->rc = w->rc;
        w->rc->parent = this->_root;
    }
    delete w;
    this->_size--;
    if (this->_root) this->updateHeight(this->_root);
    return true;
}
