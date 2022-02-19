#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
//
// Created by xjh on 1/18/2022.
//

#pragma once

#include "ListNode.h" //引入列表节点类

template<typename T>
class List { //列表模板类

private:
    int _size;
    ListNodePosi<T> header;
    ListNodePosi<T> trailer; //规模、头哨兵、尾哨兵

protected:

    void init(); //列表创建时的初始化

    int clear(); //清除所有节点

    void copyNodes(ListNodePosi<T>, int); //复制列表中自位置p起的n项



public:
// 构造函数

    List() { init(); } //默认

    List(List<T> const &L); //整体复制列表L

    List(List<T> const &L, Rank r, int n); //复制列表L中自第r项起的n项

    List(ListNodePosi<T> p, int n); //复制列表中自位置p起的n项

// 析构函数
    ~List(); //释放（包含头、尾哨兵在内的）所有节点
// 只读访问接口

    [[nodiscard]] Rank size() const { return _size; } //规模

    [[nodiscard]] bool empty() const { return _size <= 0; } //判空

    T &operator[](Rank r) const; //重载，支持循秩访问（效率低）

    ListNodePosi<T> first() const { return header->succ; } //首节点位置

    ListNodePosi<T> last() const { return trailer->pred; } //末节点位置

    bool valid(ListNodePosi<T> p) //判断位置p是否对外合法
    { return p && (trailer != p) && (header != p); } //将头、尾节点等同于NULL

    ListNodePosi<T> find(T const &e) const //无序列表查找
    { return find(e, _size, trailer); }

    ListNodePosi<T> find(T const &e, int n, ListNodePosi<T> p) const; //无序区间查找

    ListNodePosi<T> search(T const &e) const //有序列表查找
    { return search(e, _size, trailer); }

    ListNodePosi<T> search(T const &e, int n, ListNodePosi<T> p) const; //有序区间查找

    ListNodePosi<T> selectMax(ListNodePosi<T> p, int n); //在p及其n-1个后继中选出最大者

    ListNodePosi<T> selectMax() { return selectMax(header->succ, _size); } //整体最大者

// 可写访问接口

    ListNodePosi<T> insertAsFirst(T const &e); //将e当作首节点插入

    ListNodePosi<T> insertAsLast(T const &e); //将e当作末节点插入

    ListNodePosi<T> insert(ListNodePosi<T> p, T const &e); //将e当作p的后继插入

    ListNodePosi<T> insert(T const &e, ListNodePosi<T> p); //将e当作p的前驱插入

    T remove(ListNodePosi<T> p); //删除合法位置p处的节点,返回被删除节点


// 排序

    void merge(List<T> &L) { merge(header->succ, _size, L, L.header->succ, L._size); } //全列表归并

    ListNodePosi<T> merge(ListNodePosi<T>&, int, List<T> &, ListNodePosi<T>, int); //归并

    void mergeSort(ListNodePosi<T>&, int); //对从p开始连续的n个节点归并排序

    void selectionSort(ListNodePosi<T>, int); //对从p开始连续的n个节点选择排序

    void insertionSort(ListNodePosi<T>, int); //对从p开始连续的n个节点插入排序

//    void radixSort(ListNodePosi<T>, int); //对从p开始连续的n个节点基数排序

    int deduplicate(); //无序去重

    int uniquify(); //有序去重

    void reverse(); //前后倒置（习题）
// 遍历
    void traverse(void (* )(T &)); //遍历，依次实施visit操作（函数指针，只读或局部性修改）

    template<typename VST>
    void traverse(VST); //遍历，依次实施visit操作（函数对象，可全局性修改）
};

template<typename T>
List<T>::List(const List<T> &L) {
    copyNodes(L.first(), L.size());
}

template<typename T>
List<T>::List(const List<T> &L, Rank r, int n) {
    ListNodePosi<T> p = L.first();
    while (r--) p = p->succ;
    copyNodes(p, n);
}

template<typename T>
List<T>::List(ListNodePosi<T> p, int n) {
    copyNodes(p, n);

}

template<typename T>
void List<T>::init() {
    _size = 0;
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = nullptr;
    trailer->pred = header;
    trailer->succ = nullptr;
}

template<typename T>
int List<T>::clear() {
    int oldSize = _size;
    while (_size > 0) remove(header->succ);
    return oldSize;
}

template<typename T>
List<T>::~List() {
    clear();
    delete header;
    delete trailer;
}

template<typename T>
T &List<T>::operator[](Rank r) const {
    ListNodePosi<T> p = first();
    while (0 < r--)p = p->succ;
    return p->data;

}

template<typename T>
ListNodePosi<T> List<T>::insertAsFirst(const T &e) {
    _size++;
    return header->insertAsSucc(e);
}

template<typename T>
ListNodePosi<T> List<T>::insertAsLast(const T &e) {
    _size++;
    return trailer->insertAsPred(e);
}

template<typename T>
ListNodePosi<T> List<T>::insert(ListNodePosi<T> p, const T &e) {
    _size++;
    return p->insertAsSucc(e);
}

template<typename T>
ListNodePosi<T> List<T>::insert(const T &e, ListNodePosi<T> p) {
    _size++;
    return p->insertAsPred(e);

}

template<typename T>
void List<T>::copyNodes(ListNodePosi<T> p, int n) {
    init();
    while (n--) {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template<typename T>
T List<T>::remove(ListNodePosi<T> p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

template<typename T>
int List<T>::deduplicate() {
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi<T> p = first();
    int r = 0;
    while (r < _size) {
        ListNodePosi<T> q = find(p->data, r, p);
        q ? remove(q) : r++;
        p = p->succ;
    }

    return oldSize - _size;
}

template<typename T>
ListNodePosi<T> List<T>::find(const T &e, int n, ListNodePosi<T> p) const {
    while (n-- > 0) {
        p = p->pred;
        if (p->data == e) {
            return p;
        }
    }
    return nullptr;
}

template<typename T>
void List<T>::reverse() {
    if (_size < 2) return;
    ListNodePosi<T> p1 = trailer;
    ListNodePosi<T> p2 = p1->pred;
    ListNodePosi<T> p3 = p2->pred;
    trailer->pred = nullptr;
    trailer->succ = p2;
    header = trailer;
    while (p3 != nullptr) {
        p2->pred = p1;
        p2->succ = p3;
        p1 = p2;
        p2 = p3;
        p3 = p3->pred;
    }
    p2->pred = p1;
    p2->succ = nullptr;
    trailer = p2;
}


template<typename T>
template<typename VST>
void List<T>::traverse(VST lambda) {
    ListNodePosi<T> p = header;
    while ((p = p->succ) != trailer) lambda(p);
}

template<typename T>
void List<T>::traverse(void (*f)(T &)) {
    ListNodePosi<T> p = header;
    while ((p = p->succ) != trailer) f(p);
}

template<typename T>
int List<T>::uniquify() {
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi<T> p = first();
    ListNodePosi<T> q;
    while (trailer != (q = p->succ)) {
        if (q->data != p->data) {
            p = q;
        } else {
            remove(q);
        }
    }
    return oldSize - _size;
}

template<typename T>
ListNodePosi<T> List<T>::search(const T &e, int n, ListNodePosi<T> p) const {
    while (0 < n--) {
        p = p->pred;
        if (p->data <= e)return p;
    }
    return p->pred;
}

template<typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, int n) {
    ListNodePosi<T> max = p;
    while (0 < n--) {
        if (p->data > max->data) max = p;
        p = p->succ;
    }
    return max;
}

template<typename T>
void List<T>::insertionSort(ListNodePosi<T> p, int n) {
    int r = 0;
    while (r < n) {
        ListNodePosi<T> q = search(p->data, r++, p);
        insert(q, remove((p = p->succ)->pred));
    }
}

template<typename T>
void List<T>::selectionSort(ListNodePosi<T> p, int n) {
    ListNodePosi<T> q = p;
    for (int i = 0; i < n - 1; ++i) {
        q = q->succ;
    }
    for (; n > 1; n--) {
        std::swap(q->data, selectMax(p, n)->data);
        q = q->pred;
    }
}

template<typename T>
ListNodePosi<T> List<T>::merge(ListNodePosi<T>& p, int n, List<T> &L, ListNodePosi<T> q, int m) {
    ListNodePosi<T> pp = p->pred;
    while (m > 0) {
        if (n > 0 && p->data <= q->data) {
            if (q == (p = p->succ)) break;
            n--;
        } else {
            insert(L.remove((q = q->succ)->pred), p);
            m--;
        }
    }

    return p = pp->succ;
}

template<typename T>
void List<T>::mergeSort(ListNodePosi<T>& p, int n) {
    if (n < 2) return;
    int mid = n >> 1;
    ListNodePosi<T> q = p;
    for (int i = 0; i < mid; ++i) q = q->succ;
    mergeSort(p, mid);
    mergeSort(q, n - mid);
    merge(p, mid, *this, q, n - mid);
}


//List

#pragma clang diagnostic pop