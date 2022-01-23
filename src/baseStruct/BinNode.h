//
// Created by xjh on 1/23/2022.
//

#pragma once


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
//    int size(); //统计当前节点后代总数，亦即以其为根的子树的规模

    BinNodePosi<T> insertAsLC(T const &); //作为当前节点的左孩子插入新节点

    BinNodePosi<T> insertAsRC(T const &); //作为当前节点的右孩子插入新节点

//    BinNodePosi<T> succ(); //取当前节点的直接后继
//    template <typename VST> void travLevel ( VST& ); //子树层次遍历
//    template <typename VST> void travPre ( VST& ); //子树先序遍历
//    template <typename VST> void travIn ( VST& ); //子树中序遍历
//    template <typename VST> void travPost ( VST& ); //子树后序遍历
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

