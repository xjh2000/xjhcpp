//
// Created by xjh on 3/20/2022.
//


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma once

#include "QuadlistNode.h" //引入Quadlist节点类
#include "../List/ListNode.h"

template <typename T>
class Quadlist
{
    //Quadlist模板类
private:
    int _size{};
    QListNodePosi<T> header, trailer; //规模、头哨兵、尾哨兵
protected:
    void init(); //Quadlist创建时的初始化
    int clear(); //清除所有节点
public:
    //// 构造函数
    Quadlist() { init(); } //默认
    //// 析构函数
    ~Quadlist()
    {
        clear();
        delete header;
        delete trailer;
    } //删除所有节点，释放哨兵
    // 只读访问接口
    [[nodiscard]] Rank size() const { return _size; } //规模
    [[nodiscard]] bool empty() const { return _size <= 0; } //判空
    QListNodePosi<T> first() const { return header->succ; } //首节点位置
    QListNodePosi<T> last() const { return trailer->pred; } //末节点位置
    bool valid(QListNodePosi<T> p) //判断位置p是否对外合法
    {
        return p && (trailer != p) && (header != p);
    }

    // 可写访问接口

    T remove(QListNodePosi<T> p); //删除（合法）位置p处的节点，返回被删除节点的数值
    QListNodePosi<T> //将*e作为p的后继、b的上邻插入
    insertAfterAbove(const T& e, QListNodePosi<T> p, QListNodePosi<T> b = nullptr);
    //// 遍历
    //    void traverse ( void (* ) ( T& ) ); //遍历各节点，依次实施指定操作（函数指针，只读或局部修改）
    //    template <typename VST> //操作器
    //    void traverse ( VST& ); //遍历各节点，依次实施指定操作（函数对象，可全局性修改节点）
};

template <typename T>
void Quadlist<T>::init()
{
    header = new QuadlistNode<T>();
    trailer = new QuadlistNode<T>();
    header->succ = trailer;
    trailer->pred = header;
    _size = 0;
}

template <typename T>
int Quadlist<T>::clear()
{
    int oldSize = _size;
    while (0 < _size) remove(header->succ);
    return oldSize;
}

template <typename T>
T Quadlist<T>::remove(QListNodePosi<T> p)
{
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    _size--;
    T e = p->entry;
    delete p;
    return e;
}

template <typename T>
QListNodePosi<T> Quadlist<T>::insertAfterAbove(const T& e, QListNodePosi<T> p, QListNodePosi<T> b)
{
    _size++;
    return p->insertAsSuccAbove(e, b);
}


#pragma clang diagnostic pop
