//
// Created by xjh on 3/3/2022.
//

#pragma once

#include "BST.h" //基于BST实现RedBlack

template <typename T>
class RedBlack : public BST<T>
{
    //RedBlack树模板类
protected:
    void solveDoubleRed(BinNodePosi<T> x); //双红修正

    void solveDoubleBlack(BinNodePosi<T> x); //双黑修正

    int updateHeight(BinNodePosi<T> x) override; //更新节点x的高度

public:
    BinNodePosi<T> insert(const T& e); //插入（重写）

    bool remove(const T& e) override; //删除（重写）

    // BST::search()等其余接口可直接沿用
};

template <typename T>
int RedBlack<T>::updateHeight(BinNodePosi<T> x)
{
    return x->height = IsBlack(x) + std::max(stature(x->lc), stature(x->rc));
}

template <typename T>
BinNodePosi<T> RedBlack<T>::insert(const T& e)
{
    auto x = this->search(e);
    if (x) return x;
    x = new BinNode<T>(e, this->_hot, nullptr, nullptr, -1);
    ++this->_size;
    solveDoubleRed(x);
    return x ? x : this->_hot->parent;
}

template <typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi<T> x)
{
    if (IsRoot(*x))
    {
        this->_root = x;
        this->_root->color = RB_BLACK;
        ++this->_root->height;
        return;
    }

    BinNodePosi<T> p = x->parent;
    if (IsBlack(p)) return;
    BinNodePosi<T> g = p->parent;
    BinNodePosi<T> u = uncle(x);

    if (IsBlack(u))
    {
        if (IsLChild(*x) == IsLChild(*p))
        {
            p->color = RB_BLACK;
        }
        else
        {
            x->color = RB_BLACK;
        }
        g->color = RB_RED;
        BinNodePosi<T> gg = g->parent;
        if (IsRoot(*g))
        {
            this->_root = this->rotateAt(x);
        }
        else
        {
            BinNodePosi<T> r = FromParentTo(*g) = this->rotateAt(x);
            r->parent = gg;
        }
    }
    else
    {
        p->color = RB_BLACK;
        ++p->height;
        u->color = RB_BLACK;
        ++u->height;
        if (!IsRoot(*g)) g->color = RB_RED;
        solveDoubleRed(g);
    }
}

template <typename T>
bool RedBlack<T>::remove(const T& e)
{
    BinNodePosi<T> x = this->search(e);
    if (!x) return false;
    BinNodePosi<T> r = this->removeAt(x);
    if (!(--this->_size))
    {
        this->_root = nullptr;
        return true;
    }
    if (!this->_hot)
    {
        this->_root = r;
        r->color = RB_BLACK;
        updateHeight(r);
        return true;
    }
    if (BlackHeightUpdated(*this->_hot))
    {
        return true;
    }
    if (IsRed(r))
    {
        r->color = RB_BLACK;
        ++r->height;
        return true;
    }
    solveDoubleBlack(r);
    return true;
}

template <typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi<T> r)
{
    BinNodePosi<T> p = r ? r->parent : this->_hot;
    if (!p) return;
    BinNodePosi<T> s = (r == p->lc) ? p->rc : p->lc;
    if (IsBlack(s))
    {
        BinNodePosi<T> t = nullptr;
        if (IsRed(s->rc)) t = s->rc;
        if (IsRed(s->lc)) t = s->lc;
        if (t)
        {
            RBColor oldColor = p->color;
            BinNodePosi<T> b = FromParentTo(*p) = this->rotateAt(t);
            if (HasLChild(*b))
            {
                b->lc->color = RB_BLACK;
                updateHeight(b->lc);
            }
            if (HasRChild(*b))
            {
                b->rc->color = RB_BLACK;
                updateHeight(b->rc);
            }
            b->color = oldColor;
            updateHeight(b);
        }
        else
        {
            s->color = RB_RED;
            --s->height;
            if (IsRed(p))
            {
                p->color = RB_BLACK;
            }
            else
            {
                --p->height;
                solveDoubleBlack(p);
            }
        }
    }
    else
    {
        s->color = RB_BLACK;
        p->color = RB_RED;
        BinNodePosi<T> t = IsLChild(*s) ? s->lc : s->rc;
        this->_hot = p;
        FromParentTo(*p) = this->rotateAt(t);
        solveDoubleBlack(r);
    }
}
