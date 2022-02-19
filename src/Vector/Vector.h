#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"


//
// Created by 93462 on 1/12/2022.
//

#pragma once


#include <utility>
#include <stdexcept>

using Rank = int; //秩
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）

template<typename T>
class Vector { //向量模板类
protected:
    Rank _size;
    int _capacity;
    T *_elem; //规模、容量、数据区

    void copyFrom(T const *A, Rank lo, Rank hi); //复制数组区间A[lo, hi)

    void expand(); //空间不足时扩容

    void shrink(); //装填因子过小时压缩


//    void heapSort ( Rank lo, Rank hi ); //堆排序（稍后结合完全堆讲解）
//    Rank partition ( Rank lo, Rank hi ); //轴点构造算法
//    void quickSort ( Rank lo, Rank hi ); //快速排序算法
//    void shellSort ( Rank lo, Rank hi ); //希尔排序算法
public:
// 构造函数

    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c、规模为s、所有元素初始为v
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _size++) _elem[_size] = v;
    } //s<=c

    Vector(T const *A, Rank n) { copyFrom(A, 0, n); } //数组整体复制

    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //区间

    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); } //向量整体复制

    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //区间
// 析构函数
    ~Vector() { delete[] _elem; } //释放内部空间
// 只读访问接口

    [[nodiscard]] Rank size() const { return _size; } //规模

    [[nodiscard]] bool empty() const { return !_size; } //判空

    Rank find(T const &e) const { return find(e, 0, _size); } //无序向量整体查找

    Rank find(T const &e, Rank lo, Rank hi) const; //无序向量区间查找

//    Rank search ( T const& e ) const //有序向量整体查找
//    { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
//    Rank search ( T const& e, Rank lo, Rank hi ) const; //有序向量区间查找

    Rank binSearch(T const &e) const //二分查找
    { return (0 >= _size) ? -1 : binSearch(e, 0, _size); }

    Rank binSearch(T const &e, Rank lo, Rank hi) const;

// 可写访问接口

    T &operator[](Rank r); //重载下标操作符，可以类似于数组形式引用各元素

    const T &operator[](Rank r) const; //仅限于做右值的重载版本

    Vector<T> &operator=(Vector<T> const &); //重载赋值操作符，以便直接克隆向量

    T remove(Rank r); //删除秩为r的元素

    int remove(Rank lo, Rank hi); //删除秩在区间[lo, hi)之内的元素

    Rank insert(Rank r, T const &e); //插入元素

    Rank insert(T const &e) { return insert(_size, e); } //默认作为末元素插入

    void unsort(Rank lo, Rank hi); //对[lo, hi)置乱

    void unsort() { unsort(0, _size - 1); } //整体置乱

    int deduplicate(); //无序去重 o（n*n）

    int uniquify(); //有序去重 o（n*n）

    int uniquify1(); //有序去重高效版o（n）

    int disordered(); // 返回向量中逆序相邻元素的总个数


// 排序

    bool bubble(Rank lo, Rank hi); //扫描交换 有序返回 true

    void bubbleSort(Rank lo, Rank hi); //起泡排序算法

    Rank maxItem(Rank lo, Rank hi); //选取最大元素

    void selectionSort(Rank lo, Rank hi); //选择排序算法

    void merge(Rank lo, Rank mi, Rank hi); //归并算法

    void mergeSort(Rank lo, Rank hi); //归并排序算法

// 遍历

    void traverse(void (* )(T &)); //遍历（使用函数指针，只读或局部性修改）

    template<typename VST>
    void traverse(VST); //遍历（使用lambda）
};

template<typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return;
    if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; ++i) _elem[i] = oldElem[i];
    delete[] oldElem;
}

template<typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) return;
    if (_size << 2 > _capacity) return;
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; ++i) _elem[i] = oldElem[i];
    delete[] oldElem;
}

template<typename T>
void Vector<T>::copyFrom(const T *A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi) {
        _elem[_size++] = A[lo++];
    }
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &V) {
    if (&V == this) return *this;
    delete[] _elem;
    copyFrom(V._elem, 0, V.size());
    return *this;
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T &e) {
    if (r > _size) return -1;
    expand();
    for (int i = _size; i > r; --i) _elem[i] = _elem[i - 1];
    _elem[r] = e;
    _size++;
    return r;
}

template<typename T>
const T &Vector<T>::operator[](Rank r) const {
    if (r < 0 || r >= _size) throw std::out_of_range("Vector out of range");
    return _elem[r];
}

template<typename T>
T &Vector<T>::operator[](Rank r) {
    if (r < 0 || r >= _size) throw std::out_of_range("Vector out of range");
    return _elem[r];
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    T *V = _elem + lo;
    for (int i = hi - lo; i > 0; --i) std::swap(V[i], V[rand() % i]);
}

template<typename T>
T Vector<T>::remove(Rank r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi) return 0;
    while (hi < _size) _elem[lo++] = _elem[hi++];
    _size -= hi - lo;
    shrink();
    return hi - lo;
}

template<typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}

template<typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    for (int i = 1; i < _size;) {
        find(_elem[i], 0, i) >= 0 ? remove(i) : i++;
    }
    return oldSize - _size;
}

template<typename T>
void Vector<T>::traverse(void (*visit)(T &)) {
    for (int i = 0; i < _size; ++i) {
        visit(_elem[i]);
    }
}

template<typename T>
template<typename VST>
void Vector<T>::traverse(VST visit) {
    for (int i = 0; i < _size; ++i) {
        visit(_elem[i]);
    }
}

template<typename T>
int Vector<T>::uniquify() {
    int oldSize = _size;
    int i = 1;
    while (i < _size) _elem[i - 1] == _elem[i] ? remove(i) : i++;
    return oldSize - _size;
}

template<typename T>
int Vector<T>::uniquify1() {
    int i = 0, j = 0;
    while (++j < _size) {
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    }
    _size = ++i;
    shrink();
    return j - i;
}

template<typename T>
Rank Vector<T>::binSearch(const T &e, Rank lo, Rank hi) const {
    while (lo < hi) {
        Rank mid = (lo + hi) >> 1;
        e < _elem[mid] ? hi = mid : lo = mid + 1;
    }
    return --lo;
}

template<typename T>
int Vector<T>::disordered() {
    int count = 0;
    for (int i = 1; i < _size; ++i) {
        if (_elem[i - 1] > _elem[i]) ++count;
    }
    return count;
}

template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    while (!bubble(lo, hi--));
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
    bool status = true;
    for (int i = lo + 1; i < hi; ++i) {
        if (_elem[i - 1] > _elem[i]) {
            std::swap(_elem[i - 1], _elem[i]);
            status = false;
        }
    }
    return status;
}

template<typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {
    for (int i = hi; i > lo; --i) {
        std::swap(_elem[i - 1], _elem[maxItem(lo, i)]);
    }
}

template<typename T>
Rank Vector<T>::maxItem(Rank lo, Rank hi) {
    Rank max = lo;
    for (int i = lo; i < hi; ++i) {
        if (_elem[i] > _elem[max]) {
            max = i;
        }
    }
    return max;
}

template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo < 2) return;
    Rank mi = (lo + hi) / 2;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T *A = _elem + lo;
    Rank lb = mi - lo;
    T *B = new T[lb];
    T *C = _elem + mi;
    Rank lc = hi - mi;
    for (int i = 0; i < lb; ++i) {
        B[i] = A[i];
    }
    for (int a = 0, b = 0, c = 0; (b < lb) || (c < lc);) {
        if ((b < lb) && ((c >= lc) || (B[b] <= C[c])))A[a++] = B[b++];
        if ((c < lc) && ((b >= lb) || (C[c] < B[b])))A[a++] = C[c++];
    }
    delete[] B;
}






//Vector

#pragma clang diagnostic pop



