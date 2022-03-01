//
// Created by xjh on 2/28/2022.
//

#pragma once

#include "BTNode.h" //引入B-树节点类

template<typename T>
class BTree { //B-树模板类
protected:
    int _size; //存放的关键码总数

    int _order; //B-树的阶次，至少为3——创建时指定，一般不能修改

    BTNodePosi<T> _root; //根节点

    BTNodePosi<T> _hot; //BTree::search()最后访问的非空（除非树空）的节点位置

    void solveOverflow(BTNodePosi<T>); //因插入而上溢之后的分裂处理

//    void solveUnderflow(BTNodePosi<T>); //因删除而下溢之后的合并处理
public:
    explicit BTree(int order = 3) : _order(order), _size(0) //构造函数：默认为最低的3阶
    { _root = new BTNode<T>(); }

    ~BTree() { if (_root) delete _root; } //析构函数：释放所有节点

    int order() { return _order; } //阶次

    int size() { return _size; } //规模

    BTNodePosi<T> &root() { return _root; } //树根

    [[nodiscard]] bool empty() const { return !_root; } //判空

    BTNodePosi<T> search(const T &e); //查找

    bool insert(const T &e); //插入

//    bool remove(const T &e); //删除
};

template<typename T>
BTNodePosi<T> BTree<T>::search(const T &e) {
    BTNodePosi<T> v = this->_root;
    this->_hot = nullptr;
    while (v) {
        Rank r = v->key.binSearch(e);
        if ((0 <= r) && (e == v->key[r])) return v;
        _hot = v;
        v = v->child[r + 1];
    }
    return nullptr;
}

template<typename T>
bool BTree<T>::insert(const T &e) {
    BTNodePosi<T> v = search(e);
    if (v) return false;
    Rank r = this->_hot->key.binSearch(e);
    this->_hot->key.insert(r + 1, e);
    this->_hot->child.insert(r + 2, nullptr);
    this->_size++;
    solveOverflow(this->_hot);
    return true;
}

template<typename T>
void BTree<T>::solveOverflow(BTNodePosi<T> v) {
    if (_order >= v->child.size()) return;
    Rank s = _order / 2;
    auto u = new BTNode<T>();
    for (Rank j = 0; j < _order - s - 1; ++j) {
        u->child.insert(j, v->child.remove(s + 1));
        u->key.insert(j, v->key.remove(s + 1));
    }
    
    u->child[_order - s - 1] = v->child.remove(s + 1);
    for (Rank j = 0; j < _order - s; ++j) if (u->child[j]) u->child[j]->parent = u;

    auto p = v->parent;
    if (!p) {
        _root = p = new BTNode<T>();
        p->child[0] = v;
        v->parent = p;
    }

    auto r = p->key.binSearch(v->key[0]);

    p->key.insert(r + 1, v->key.remove(s));
    p->child.insert(r + 2, u);

    u->parent = p;
    solveOverflow(p);
}
//BTree