//
// Created by xjh on 3/20/2022.
//


#pragma once
#include <cstdlib>
#include "../Entry/Entry.h"
#include "../List/List.h" //引入列表
#include "Quadlist.h" //引入Quadlist
#include "Dictionary.h" //引入词典

template <typename K, typename V> //key、value
//符合Dictionary接口的Skiplist模板类（但隐含假设元素之间可比较大小）
class Skiplist : public Dictionary<K, V>, public List<Quadlist<Entry<K, V>>*>
{
protected:
    bool skipSearch(
        ListNode<Quadlist<Entry<K, V>>*>*& qlist,
        QuadlistNode<Entry<K, V>>*& p,
        K& k);

public:
    [[nodiscard]] int size() const override;
    //底层Quadlist的规模
    int level() { return this->size(); } //层高 == #Quadlist，不一定要开放
    bool put(K, V) override; //插入（注意与Map有别——Skiplist允许词条重复，故必然成功）
    V* get(K k) override; //读取
    bool remove(K k) override; //删除
};

template <typename K, typename V>
bool Skiplist<K, V>::skipSearch(ListNode<Quadlist<Entry<K, V>>*>*& qlist, QuadlistNode<Entry<K, V>>*& p, K& k)
{
    while (true)
    {
        while (p->succ && (p->entry.key <= k)) p = p->succ;
        p = p->pred;
        if (p->pred && (k == p->entry.key)) return true;
        qlist = qlist->succ;
        if (!qlist->succ) return false;
        p = (p->pred) ? p->below : qlist->data->first();
    }
}

template <typename K, typename V>
int Skiplist<K, V>::size() const
{
    return this->empty() ? 0 : this->last()->data->size();
}

template <typename K, typename V>
V* Skiplist<K, V>::get(K k)
{
    ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first();
    QuadlistNode<Entry<K, V>>* p = qlist->data->first();
    return skipSearch(qlist, p, k) ? &(p->entry.value) : nullptr;
}

template <typename K, typename V>
bool Skiplist<K, V>::put(K k, V v)
{
    Entry<K, V> e = Entry<K, V>(k, v);
    if (this->empty()) this->insertAsFirst(new Quadlist<Entry<K, V>>);
    ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first();
    QuadlistNode<Entry<K, V>>* p = qlist->data->first();
    if (skipSearch(qlist, p, k)) while (p->below) p = p->below;
    qlist = this->last();
    QuadlistNode<Entry<K, V>>* b = qlist->data->insertAfterAbove(e, p);
    while (rand() & 1)
    {
        while (qlist->data->valid(p) && !p->above) p = p->pred;
        if (!qlist->data->valid(p))
        {
            if (qlist == this->first()) this->insertAsFirst(new Quadlist<Entry<K, V>>);
            p = qlist->pred->data->first()->pred;
        }
        else p = p->above;
        qlist = qlist->pred;
        b = qlist->data->insertAfterAbove(e, p, b);
    }
    return true;
}

template <typename K, typename V>
bool Skiplist<K, V>::remove(K k)
{
    if (this->empty()) return false;
    ListNode<Quadlist<Entry<K, V>>*>* qlist = this->first();
    QuadlistNode<Entry<K, V>>* p = qlist->data->first();
    if (!skipSearch(qlist, p, k)) return false;
    do
    {
        QuadlistNode<Entry<K, V>>* lower = p->below;
        qlist->data->remove(p);
        p = lower;
        qlist = qlist->succ;
    }
    while (qlist->succ);
    qlist = this->first();
    while (!this->empty() && qlist->data->empty())
    {
        List<Quadlist<Entry<K, V>>*>::remove(this->first());
        qlist = this->first();
    }
    return true;
}
