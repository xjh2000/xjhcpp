//
// Created by xjh on 1/23/2022.
//

#pragma once
#include "vector"
#include "deque"

/******************************************************************************************
 * BinNode状态与性质的判断
 ******************************************************************************************/
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )

/******************************************************************************************
 * 与BinNode具有特定关系的节点及指针
 ******************************************************************************************/
#define sibling(p) ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc ) /*兄弟*/
#define uncle(x) ( sibling( (x)->parent ) ) /*叔叔*/
#define FromParentTo(x) ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )


#if defined( DSA_REDBLACK )
#define stature(p) ((p) ? (p)->height : 0) //红黑树节点的黑高度（NULL视作外部节点，对应于0）
#else
#define stature(p) ((p) ? (p)->height : -1) //其余BST中节点的高度（NUll视作空树，对应于-1）
#endif
typedef enum {
    RB_RED, RB_BLACK
} RBColor; //节点颜色

template<typename T>
struct BinNode;

template<typename T> using BinNodePosi = BinNode<T> *; //节点位置

template<typename T>
struct BinNode { //二叉树节点模板类
// 成员（为简化描述起见统一开放，读者可根据需要进一步封装）
    T data; //数值
    BinNodePosi<T> parent, lc, rc; //父节点及左、右孩子
    int height; //高度（通用）
    int npl; //Null Path Length（左式堆，也可直接用height代替）
    RBColor color; //颜色（红黑树）
// 构造函数
    BinNode() :
            parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), color(RB_RED) {}

    explicit BinNode(T e, BinNodePosi<T> p = nullptr, BinNodePosi<T> lc = nullptr, BinNodePosi<T> rc = nullptr,
                     int h = 0, int l = 1, RBColor c = RB_RED) :
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

// 操作接口
    int size(); //统计当前节点后代总数，亦即以其为根的子树的规模

    BinNodePosi<T> insertAsLC(T const &); //作为当前节点的左孩子插入新节点

    BinNodePosi<T> insertAsRC(T const &); //作为当前节点的右孩子插入新节点

    BinNodePosi<T> succ(); //取当前节点的直接后继

    template <typename VST> void travLevel ( VST visit ); //子树层次遍历

    template <typename VST> void travPre_R ( BinNodePosi<T> x, VST visit); //子树先序遍历递归

    template <typename VST> void travIn_R ( BinNodePosi<T> x, VST visit ); //子树中序遍历递归

    template <typename VST> void travPost_R ( BinNodePosi<T> x, VST visit ); //子树中序遍历递归

    template <typename VST> void travPre ( VST visit ); //子树先序遍历迭代

    template <typename VST> void travIn ( VST visit ); //子树中序遍历迭代

    template <typename VST> void travIn_1 ( VST visit ); //子树中序遍历迭代

    template <typename VST> void travPost ( VST visit ); //子树后序遍历

// 比较器、判等器（各列其一，其余自行补充）
    bool operator<(BinNode const &bn) { return data < bn.data; } //小于
    bool operator==(BinNode const &bn) { return data == bn.data; } //等于
    /*DSA*/

//    BinNodePosi<T> zig(); //顺时针旋转
//    BinNodePosi<T> zag(); //逆时针旋转
//    BinNodePosi<T> balance(); //完全平衡化
//    BinNodePosi<T> imitate( const BinNodePosi<T> );

};

template<typename T>
BinNodePosi<T> BinNode<T>::insertAsRC(const T &e) {
    return rc = new BinNode<T>(e, this);
}

template<typename T>
BinNodePosi<T> BinNode<T>::insertAsLC(const T &e) {
    return lc = new BinNode<T>(e, this);
}

template<typename T>
int BinNode<T>::size() {
    std::vector<BinNodePosi<T>> v;
    int n = 1;
    v.push_back(this);
    while (v.size() != 0) {
        BinNodePosi<T> x = v.back();
        v.pop_back();
        if (x->lc != nullptr) {
            v.push_back(x->lc);
            n++;
        }
        if (x->rc != nullptr) {
            v.push_back(x->rc);
            n++;
        }
    }
    return n;
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre_R(BinNodePosi<T> x, VST visit) {
    if (!x) return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn_R(BinNodePosi<T> x, VST visit) {
    if (!x) return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

template<typename T>
template<typename VST>
void BinNode<T>::travPost_R(BinNodePosi<T> x, VST visit) {
    if (!x) return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST visit) {
    std::vector<BinNodePosi<T>> S;
    BinNodePosi<T> x = this;
    while (true) {
        while (x){
            visit(x->data);
            if (HasRChild(*x)) S.push_back(x->rc);
            x = x->lc;
        }
        if (S.empty()) break;
        x = S.back();
        S.pop_back();
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn(VST visit) {
    std::vector<BinNodePosi<T>> S;
    BinNodePosi<T> x = this;
    while (true) {
        while (x){
            S.push_back(x);
            x = x->lc;
        }
        if (S.empty()) break;
        x = S.back();
        visit(x->data);
        S.pop_back();
        x = x->rc;
    }

}

template<typename T>
BinNodePosi<T> BinNode<T>::succ() {
    BinNodePosi<T> s = this;
    if (rc) {
        s = rc;
        while (HasLChild(*s)) s = s->lc;
    } else {
        while (IsRChild(*s)) s = s->parent;
        s = s->parent;
    }
    return s;
}

template<typename T>
template<typename VST>
void BinNode<T>::travIn_1(VST visit) {
    bool backTrack = false;
    BinNodePosi<T> x = this;
    while (true) {
        if ((!backTrack)&&(HasLChild(*x))) x = x->lc;
        else{
            visit(x->data);
            if (HasRChild(*x)) {
                backTrack = false;
                x = x->rc;
            } else {
                if (!(x=x->succ())) break;
                backTrack = true;
            }
        }
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travPost(VST visit) {
    std::vector<BinNodePosi<T>> S;
    BinNodePosi<T> x = this;
    S.push_back(x);
    while (!S.empty()) {
        if (S.back() != x->parent) {
            while (BinNodePosi<T> node = S.back()) {
                if (HasLChild(*node)) {
                    if (HasRChild(*node)) S.push_back(node->rc);
                    S.push_back(node->lc);
                } else {
                    S.push_back(node->rc);
                }
            }
            S.pop_back();
        }
        x = S.back();
        S.pop_back();
        visit(x->data);
    }
}

template<typename T>
template<typename VST>
void BinNode<T>::travLevel(VST visit) {
    std::deque<BinNodePosi<T>> S;
    BinNodePosi<T> x = this;
    S.push_back(x);
    while (!S.empty()) {
        x = S.front();
        S.pop_front();
        visit(x->data);
        if (HasLChild(*x))S.push_back(x->lc);
        if (HasRChild(*x))S.push_back(x->rc);
    }
}



