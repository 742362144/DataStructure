//
// Created by Coder on 2018/2/13.
//

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

template <class Type, class Weight>
class DirectedGraph{

private:
    //最大顶点数
    const static int V = 10000;

    //当前的顶点数
    int VertexCount = 0;

    //存储所有的顶点
    vector<Type> vertexs;

    // vector实现的邻接表的定义
    // 注意edge[i]中的每一个元素都表示节点vertex数组中的下标
    // edge[i][j]表示 vertex[i]与vertex[edge[i][j]]有通路
    vector<int> edge[V];
    //weight和数组edge一一对应
    //weight[i][j]表示 vertex[i]与vertex[edge[i][j]]通路的权
    vector<Weight> weight[V];
    int visit[V];

public:

    DirectedGraph() {
        // 邻接表的初始化操作
        // 将起点为`i`的边链表全部清空
        for (int i=0; i<V; i++) {
            edge[i].clear();
            visit[i] = -1;
        }
    }

    bool SearchVertex(Type v) {
        for (int i=0; i<vertexs.size(); i++) {
            if (vertexs[i] == v) {
                return true;
            }
        }
        return false;
    }

    bool InsertVertex(Type v) {
        if(!SearchVertex(v)) {
            vertexs.push_back(v);
            VertexCount++;
            return true;
        }
        return false;
    }

    int FindIndex(Type v) {
        for (int i=0; i<vertexs.size(); i++) {
            if (vertexs[i] == v) {
                return i;
            }
        }
        return -1;
    }

    bool InsertEdge(Type from, Type to, Weight w) {
        int i = FindIndex(from);
        int j = FindIndex(to);
        if(i != -1 && j != -1) {
            //添加边
            edge[i].push_back(j);
            //添加权
            weight[i].push_back(w);
        }
    }

    bool Visited(int index) {
        return visit[index] != -1;
    }

    //访问vertexs[index]
    void Visit(int index) {
        visit[index] = 1;
        cout<<vertexs[index]<<endl;
    }


    // 查询边
    bool SearchEdge( Type from, Type to) {
        int i = FindIndex(from);
        int j = FindIndex(to);
        if (i != -1) {
            for (int k=0; k<(int)edge[i].size(); ++k) {
                if (edge[i][k] == j) {     // 查询边`i->j`
                    return true;
                }
            }
        }
        return false;
    }

    // 查询边
    bool SearchEdgeWeight( Type from, Type to, Weight &w) {
        int i = FindIndex(from);
        int j = FindIndex(to);
        if (i != -1) {
            for (int k=0; k<(int)edge[i].size(); ++k) {
                if (edge[i][k] == j) {     // 查询边`i->j`
                    w = weight[i][k];
                    return true;
                }
            }
        }
        return false;
    }

    //打印顶点
    void PrintVertex() {
        for (int i=0; i<vertexs.size(); i++) {
            cout<<vertexs[i]<<endl;
        }
    }
    //打印边
    void PrintEdge() {
        for (int i=0; i<VertexCount; i++) {
            for (int j=0; j<edge[i].size(); j++) {
                cout<<vertexs[i]<<"->"<<vertexs[edge[i][j]]<<" weight:"<<weight[i][j]<<endl;
            }
        }
    }

    //返回v第一个没被访问的邻接点下标
    //index是v在vertexs中的下标
    int GetFirstNotVisit(int index) {
        if (index != -1) {
            //遍历v的邻接点
            for (int j=0; j<edge[index].size(); j++) {
                if(!Visited(edge[index][j]))
                    return edge[index][j];
            }
        }
        return -1;
    }

    //从v开始深度优先遍历
    void DFS(int index) {
        //访问该节点
        Visit(index);
        //存储节点的下标
        stack<int> s;
        s.push(index);
        while (!s.empty()) {
            //找到下一个待访问的邻接点下标
            int next = GetFirstNotVisit(s.top());
            if (next != -1) {   //还能继续深搜(未达到最大深度)，继续
                //找到栈顶元素第一个未被访问的临接点(也就是更深的邻接点),访问之
                Visit(next);
                //入栈
                s.push(next);
            } else {    //不能继续深搜下去，回溯
                //出栈(回溯)到能找到有邻接点未被访问的节点
                s.pop();
            }
        }
    }

    //整个图的深搜
    void DFSTraverse() {
        for (int i=0; i<VertexCount; i++) {
            if (!Visited(i)) {
                DFS(i);
            }
        }
    }

    //单节点广搜
    void BFS(int index) {
        //访问当前节点
        Visit(index);
        queue<int> s;
        s.push(index);
        while (!s.empty()) {
            //取队首元素
            int front = s.front();
            //出队
            s.pop();
            //对于队首元素，访问其所有未访问的邻接点
            //将未访问的邻接点入栈
            for (int i=0; i<edge[front].size(); i++) {
                if (!Visited(edge[front][i])) {
                    Visit(edge[front][i]);
                    s.push(edge[front][i]);
                }
            }
        }
    }

    //整个图的广搜
    void BFSTraverse() {
        for (int i=0; i<VertexCount; i++) {
            if (!Visited(i)) {
                BFS(i);
            }
        }
    }

    void ShortestPath(int index) {
        //path数组存储到各顶点的最短路径和路径上的顶点下标
        vector<int> path[VertexCount];
        Weight value[VertexCount];
        bool final[VertexCount];

        //初始化
        for (int i=0; i<VertexCount; i++) {
            path[i].clear();
            value[i] = INT32_MAX;
            final[i] = false;
        }
        value[index] = 0;
        final[index] = true;
        path[index].push_back(index);
        int k = index;

        //一共循环VertexCount-1次
        for (int i=1; i<VertexCount; i++) {
            //根据新加入的vertex[index]来更新路径权值
            for (int j=0; j<edge[k].size(); j++) {
                    //判断k到edge[k][j]的权值是否比当前value[edge[k][j]]的小,小则更新
                if (value[edge[k][j]] > value[k] + weight[k][j]) {
                    //更新权值
                    value[edge[k][j]] = value[k] + weight[k][j];
                    //更新路径
                    path[edge[k][j]].clear();
                    path[edge[k][j]].assign(path[k].begin(), path[k].end());
                    path[edge[k][j]].push_back(edge[k][j]);
                }
            }
            Weight min = INT32_MAX;
            for (int j=0; j<VertexCount; j++) {
                if (!final[j] && value[j] < min) {
                    min = value[j];
                    k = j;
                }
            }
            final[k] = true;
        }
        for (int i = 1; i < VertexCount; ++i) {
            cout<<vertexs[i]<<" ---- ";
            for (int j=0; j<path[i].size(); j++) {
                cout<<vertexs[path[i][j]]<<" ";
            }
            cout<<endl;
        }
    }
};

int main() {
    DirectedGraph<char, int> graph;
    int total, weight;
    char from, to;
    cin>>total;
    for (int i=0; i<total; i++) {
        cin>>from>>to>>weight;
        graph.InsertVertex(from);
        graph.InsertVertex(to);
        graph.InsertEdge(from, to, weight);
//        graph.InsertEdge(to, from, weight);
    }
//    graph.PrintVertex();
//    graph.PrintEdge();
//    graph.DFSTraverse();
    graph.ShortestPath(0);
    cout<<endl;
}