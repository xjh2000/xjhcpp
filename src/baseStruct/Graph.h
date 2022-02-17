//
// Created by xjh on 1/27/2022.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma once

#include <climits>
#include <deque>

using VStatus = enum {
    UNDISCOVERED, DISCOVERED, VISITED
}; //顶点状态
using EType = enum {
    UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD
}; //边在遍历树中所属的类型

template<typename Tv, typename Te> //顶点类型、边类型
class Graph { //图Graph模板类
private:
    void reset() { //所有顶点、边的辅助信息复位
        for (int i = 0; i < n; i++) { //所有顶点的
            status(i) = UNDISCOVERED;
            dTime(i) = fTime(i) = -1; //状态，时间标签
            parent(i) = -1;
            priority(i) = INT_MAX; //（在遍历树中的）父节点，优先级数
            for (int j = 0; j < n; j++) //所有边的
                if (exists(i, j)) type(i, j) = UNDETERMINED; //类型
        }
    }

    void BFS(int, int &); //（连通域）广度优先搜索算法

    void DFS(int, int &); //（连通域）深度优先搜索算法

    void BCC(int, int &, std::vector<int> &); //（连通域）基于DFS的双连通分量分解算法

    bool TSort(int, int &, std::vector<Tv> *); //（连通域）基于DFS的拓扑排序算法

    template<typename PU>
    void PFS(int, PU); //（连通域）优先级搜索框架

public:
// 顶点
    int n{}; //顶点总数
    virtual int insert(Tv const &) = 0; //插入顶点，返回编号
    virtual Tv remove(int) = 0; //删除顶点及其关联边，返回该顶点信息
    virtual Tv &vertex(int) = 0; //顶点v的数据（该顶点的确存在）
    virtual int inDegree(int) = 0; //顶点v的入度（该顶点的确存在）
    virtual int outDegree(int) = 0; //顶点v的出度（该顶点的确存在）
    virtual int firstNbr(int) = 0; //顶点v的首个邻接顶点
    virtual int nextNbr(int, int) = 0; //顶点v的（相对于顶点j的）下一邻接顶点
    virtual VStatus &status(int) = 0; //顶点v的状态
    virtual int &dTime(int) = 0; //顶点v的时间标签dTime
    virtual int &fTime(int) = 0; //顶点v的时间标签fTime
    virtual int &parent(int) = 0; //顶点v在遍历树中的父亲
    virtual int &priority(int) = 0; //顶点v在遍历树中的优先级数
// 边：这里约定，无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
    int e{}; //边总数
    virtual bool exists(int, int) = 0; //边(v, u)是否存在
    virtual void insert(Te const &, int, int, int) = 0; //在顶点v和u之间插入权重为w的边e
    virtual Te remove(int, int) = 0; //删除顶点v和u之间的边e，返回该边信息
    virtual EType &type(int, int) = 0; //边(v, u)的类型
    virtual Te &edge(int, int) = 0; //边(v, u)的数据（该边的确存在）
    virtual int &weight(int, int) = 0; //边(v, u)的权重
// 算法

    void bfs(int); //广度优先搜索算法

    void dfs(int); //深度优先搜索算法

    void bcc(int); //基于DFS的双连通分量分解算法

    std::vector<Tv> tSort(int); //基于DFS的拓扑排序算法

    void prim ( int ); //最小支撑树Prim算法

//    void dijkstra ( int ); //最短路径Dijkstra算法

    template<typename PU>
    void pfs(int, PU); //优先级搜索框架
};

template<typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) {
    reset();
    int clock = 0;
    int v = s;
    do {
        if (status(v) == UNDISCOVERED) {
            BFS(v, clock);
        }
    } while (s != (v = (++v % n)));
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int &clock) {
    std::deque<int> q;
    status(v) = DISCOVERED;
    q.push_back(v);
    while (!q.empty()) {
        int vq = q.front();
        q.pop_front();
        dTime(vq) = clock++;
        for (int u = firstNbr(vq); -1 < u; u = nextNbr(vq, u)) {
            if (UNDISCOVERED == status(u)) {
                status(u) = DISCOVERED;
                q.push_back(u);
                type(vq, u) = TREE;
                parent(u) = v;
            } else {
                type(vq, u) = CROSS;
            }
        }
        status(v) = VISITED;
    }
}


template<typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) {
    reset();
    int clock = 0;
    int v = s;
    do {
        if (status(v) == UNDISCOVERED) {
            DFS(v, clock);
        }
    } while (s != (v = (++v % n)));

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock) {
    dTime(v) = clock++;
    status(v) = DISCOVERED;
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
        switch (status(u)) {
            case UNDISCOVERED:
                type(v, u) = TREE;
                parent(u) = v;
                DFS(u, clock);
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;
                break;
            default:
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
}

template<typename Tv, typename Te>
std::vector<Tv> Graph<Tv, Te>::tSort(int s) {
    std::vector<Tv> stack;
    reset();
    int clock = 0;
    int v = s;
    do {
        if (UNDISCOVERED == status(v)) {
            if (!TSort(v, clock, &stack)) {
                while (!stack.empty())
                    stack.pop_back();
                break;
            }
        }
    } while (s != (v = (++v % n)));
    return stack;
}

template<typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int &clock, std::vector<Tv> *stack) {
    dTime(v) = clock++;
    status(v) = DISCOVERED;
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
        switch (status(u)) {
            case UNDISCOVERED:
                type(v, u) = TREE;
                parent(u) = v;
                if (!TSort(u, clock, stack)) return false;
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;
                return false;
            default:
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
    stack->push_back(vertex(v));
    return true;
}

template<typename Tv, typename Te>
void Graph<Tv, Te>::bcc(int s) {
    reset();
    int clock = 0;
    int v = s;
    std::vector<int> stack;
    do {
        if (status(v) == UNDISCOVERED) {
            BCC(v, clock, stack);
            stack.pop_back();
        }
    } while (s != (v = (++v % n)));
}

#define hca(x) (fTime(x))

template<typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int &clock, std::vector<int> &stack) {
    hca(v) = dTime(v) = clock++;
    status(v) = DISCOVERED;
    stack.push_back(v);
    for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {
        switch (status(u)) {
            case UNDISCOVERED:
                parent(u) = v;
                type(v, u) = TREE;
                BCC(u, clock, stack);
                if (hca(u) < dTime(v)) {
                    hca(v) = std::min(hca(v), hca(u));
                } else {
                    while (v != stack.back()) stack.pop_back();
                }
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;
                if (u != parent(v)) {
                    hca(v) = std::min(hca(v), dTime(u));
                }
                break;
            default:
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED;
}

#undef hca

template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater) {
    reset();
    int v = s;
    do {
        if (status(v) == UNDISCOVERED) {
            PFS(v, prioUpdater);
        }
    } while (s != (v = (++v % n)));

}

template<typename Tv, typename Te>
template<typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) {
    priority(s) = 0;
    status(s) = VISITED;
    parent(s) = -1;
    int clock = 0;
    dTime(s) = clock++;
    while (true) {
        for (int w = firstNbr(s); w > -1; w = nextNbr(s, w)) {
            prioUpdater(this, s, w);
        }
        for (int shortest = INT_MAX, w = 0; w < n; ++w) {
            if (UNDISCOVERED == status(w)) {
                if (shortest > priority(w)) {
                    shortest = priority(w);
                    s = w;
                }
            }
        }
        if (VISITED == status(s)) break;
        status(s) = VISITED;
        dTime(s) = clock++;
        type(parent(s), s) = TREE;
    }

}

template<typename Tv, typename Te>
void Graph<Tv, Te>::prim(int s) {
    pfs(s,PrimPU<Tv,Te>());
}

template<typename Tv, typename Te>
struct PrimPU {
    virtual void operator()(Graph<Tv, Te> *g, int uk, int v) {
        if (UNDISCOVERED == g->status(v)) {
            if (g->priority(v) > g->weight(uk, v)) {
                g->priority(v) = g->weight(uk, v);
                g->parent(v) = uk;
            }
        }
    }
};


#pragma clang diagnostic pop