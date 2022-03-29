//
// Created by xjh on 1/27/2022.
//

#pragma once

#include "vector"
#include "Graph.h" //引入图ADT
#include "../Vector/Vector.h"

template <typename Tv>
struct Vertex
{
    //顶点对象（为简化起见，并未严格封装）
    Tv data; // 数据
    int inDegree, outDegree; //出入度数
    VStatus status; // 状态
    int dTime, fTime; //时间标签
    int parent; // 在遍历树中的父节点数
    int priority; //在遍历树中的优先级数
    Vertex(const Tv& d = static_cast<Tv>(0)) : //构造新顶点
        data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
        dTime(-1), fTime(-1), parent(-1), priority(INT_MAX)
    {
    } //暂不考虑权重溢出
};

template <typename Te>
struct Edge
{
    //边对象（为简化起见，并未严格封装）
    Te data; //数据
    int weight; //权重
    EType type; //类型
    Edge(const Te& d = static_cast<Te>(0), int w = 0) : data(d), weight(w), type(UNDETERMINED)
    {
    } //构造
};

template <typename Tv, typename Te> //顶点类型、边类型
class GraphMatrix : public Graph<Tv, Te>
{
    //基于向量，以邻接矩阵形式实现的图
private:
    Vector<Vertex<Tv>> V; //顶点集（向量）
    Vector<Vector<Edge<Te>*>> E; //边集（邻接矩阵）
public:
    GraphMatrix() { this->n = this->e = 0; } //构造
    ~GraphMatrix()
    {
        //析构
        for (int j = 0; j < this->n; j++) //所有动态创建的
            for (int k = 0; k < this->n; k++) //边记录
                delete E[j][k]; //逐条清除
    }

    // 顶点的基本操作：查询第i个顶点（0 <= i < n）
    Tv& vertex(int i) override { return V[i].data; } //数据
    int inDegree(int i) override { return V[i].inDegree; } //入度
    int outDegree(int i) override { return V[i].outDegree; } //出度
    int firstNbr(int i) override { return nextNbr(i, this->n); } //首个邻接顶点
    int nextNbr(int i, int j) override
    //相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
    {
        while ((-1 < j) && (!exists(i, --j)));
        return j;
    } //逆向线性试探
    VStatus& status(int i) override { return V[i].status; } //状态
    int& dTime(int i) override { return V[i].dTime; } //时间标签dTime
    int& fTime(int i) override { return V[i].fTime; } //时间标签fTime
    int& parent(int i) override { return V[i].parent; } //在遍历树中的父亲
    int& priority(int i) override { return V[i].priority; } //在遍历树中的优先级数
    // 顶点的动态操作
    int insert(const Tv& vertex) override
    {
        //插入顶点，返回编号
        for (int j = 0; j < this->n; j++) E[j].insert(NULL);
        ++this->n; //各顶点预留一条潜在的关联边
        E.insert(Vector<Edge<Te>*>(this->n, this->n, static_cast<Edge<Te>*>(nullptr))); //创建新顶点对应的边向量
        return V.insert(Vertex<Tv>(vertex)); //顶点向量增加一个顶点
    }

    Tv remove(int i) override
    {
        //删除第i个顶点及其关联边（0 <= i < n）
        for (int j = 0; j < this->n; j++) //所有出边
            if (exists(i, j))
            {
                delete E[i][j];
                --V[j].inDegree;
                --this->e;
            } //逐条删除
        E.remove(i);
        --this->n; //删除第i行
        Tv vBak = vertex(i);
        V.remove(i); //删除顶点i
        for (int j = 0; j < this->n; j++) //所有入边
            if (Edge<Te>* x = E[j].remove(i))
            {
                delete x;
                --V[j].outDegree;
                --this->e;
            } //逐条删除
        return vBak; //返回被删除顶点的信息
    }

    // 边的确认操作
    bool exists(int i, int j) override
    //边(i, j)是否存在
    {
        return (0 <= i) && (i < this->n) && (0 <= j) && (j < this->n) && E[i][j] != NULL;
    }

    // 边的基本操作：查询顶点i与j之间的联边（0 <= i, j < n且exists(i, j)）
    EType& type(int i, int j) override { return E[i][j]->type; } //边(i, j)的类型
    Te& edge(int i, int j) override { return E[i][j]->data; } //边(i, j)的数据
    int& weight(int i, int j) override { return E[i][j]->weight; } //边(i, j)的权重
    // 边的动态操作
    void insert(const Te& edge, int w, int i, int j) override
    {
        //插入权重为w的边e = (i, j)
        if (exists(i, j)) return; //确保该边尚不存在
        E[i][j] = new Edge<Te>(edge, w); //创建新边
        ++this->e;
        ++V[i].outDegree;
        ++V[j].inDegree; //更新边计数与关联顶点的度数
    }

    Te remove(int i, int j) override
    {
        //删除顶点i和j之间的联边（exists(i, j)）
        Te eBak = edge(i, j);
        delete E[i][j];
        E[i][j] = NULL; //备份后删除边记录
        --this->e;
        --V[i].outDegree;
        --V[j].inDegree; //更新边计数与关联顶点的度数
        return eBak; //返回被删除边的信息
    }

    std::vector<Tv> traversalOrder()
    {
        //返回遍历顺序
        std::vector<Tv> list((this->n));
        for (int i = 0; i < this->n; ++i)
        {
            if (V[i].dTime > 0)
            {
                list[V[i].dTime] = V[i].data;
            }
        }
        return list;
    }
};
