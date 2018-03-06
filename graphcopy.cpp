//
// Created by Coder on 2018/2/13.
//

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class DirectedGraph{

private:
    // 最大顶点数
    const int V = 100000;

    //当前的顶点数
    int VertexCount = 0;

    // vector实现的邻接表的定义
    // 不考虑边权，存储类型为int型
    vector<int> e[V];
    int visit[V];

    // 邻接表的初始化操作
    // 将起点为`i`的边链表全部清空
    void init() {
        for (int i=0; i<V; i++) {
            e[i].clear();
            visit[i] = -1;
        }
    }

public:

    void InsertVertex(int vertex) {

    }

    void InsertEdge() {

    }


    bool Visited(int v) {
        return visit[v] != -1;
    }

    void Visit(int v) {
        visit[v] = 1;
        cout<<v<<endl;
    }

    // 增加边
    // 新增顶点`i`到顶点`j`的边
    void AddEdge(int i, int j) {
        e[i].push_back(j);
    }


    // 查询边
    bool SearchEdge( int j, int k) {
        for (int i=0; i<V; i++) {
            //e[i][0] ----- 查询以`i`为起点的第一条边`i->e[i][0]`
            for (int j=0; j<(int)e[i].size(); ++j) {
                if (e[i][j] == k) {     // 查询边`i->k`
                    return true;
                }
            }
        }
        return false;
    }

    int GetFirstNotVisit(int v) {
        for (int j=0; j<e[v].size(); j++) {
            if(!Visited(e[v][j]))
                return j;
        }
        return -1;
    }

    //从v开始深度优先遍历
    void DFS(int v) {
        Visit(v);
        stack<int> s;
        s.push(v);
        while (!s.empty()) {
            //找到下一个待访问的邻接点
            int next = GetFirstNotVisit(s.top());
            if (next != -1) {   //还能继续深搜(未达到最大深度)，继续
                //找到栈顶元素第一个未被访问的临接点(也就是更深的邻接点),访问之
                Visit(GetFirstNotVisit(s.top()));
                //入栈
                s.push(GetFirstNotVisit(s.top()));
            } else {    //不能继续深搜下去，回溯
                //出栈(回溯)到能找到有邻接点未被访问的节点
                s.pop();
            }
        }
    }

    //整个图的深搜
    void DFSTraverse() {
        for (int i=0; i<V; i++) {
            if (!Visited(i)) {
                DFS(i);
            }
        }
    }

    //单节点广搜
    void BFS(int v) {
        //访问当前节点
        Visit(v);
        queue<int> s;
        s.push(v);
        while (!s.empty()) {
            //取队首元素
            int front = s.front();
            //出队
            s.pop();
            //对于队首元素，访问其所有未访问的邻接点
            //将未访问的邻接点入栈
            for (int i=0; i<e[front].size(); i++) {
                if (!Visited(e[front][i])) {
                    Visit(e[front][i]);
                    s.push(e[front][i]);
                }
            }
        }
    }

    //整个图的广搜
    void BFSTraverse() {
        for (int i=0; i<V; i++) {
            if (!Visited(i)) {
                BFS(i);
            }
        }
    }


};

