/*
 * Dijkstra's algorithm
 * https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
 * O(V^2 + E) 
 * 更优的算法应该用优先队列 O(V*logV + E)
 * Input:
   6 8 1
   1 3 10
   1 5 30
   1 6 100
   2 3 5
   3 4 50
   4 6 10
   5 6 60
   5 4 20
 * */

#include <iostream>
#include <algorithm> 
#include <limits>

using namespace std;

int imax = std::numeric_limits<int>::max();

int main()
{
    int n;  // 节点数
    int m;  // 边数
    int s;  // 起点
    /*
     * u[i]、v[i]和w[i]表示第i条边是从第u[i]号顶点到v[i]号顶点（u[i]àv[i]），且权值为w[i]
     */
    int *u = NULL;
    int *v = NULL;
    int *w = NULL;

    int *first = NULL;
    int *next = NULL;

    /*
     * vis[i] 表示该边是否被访问过
     * dis[i] 表示从起点到该节点的距离
     * pre[i] 表示该节点的上一节点
     */
    int *vis = NULL;
    int *dis = NULL;
    int *pre = NULL;

    cin >> n >> m >> s;

    u = new int[m];
    v = new int[m];
    w = new int[m];

    first = new int[n];
    next = new int[m];

    vis = new int[n];
    dis = new int[n];
    pre = new int[n];

    fill_n(first, n, -1);

    /* 初始化邻接表 */
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[i];

        next[i] = first[u[i] - 1];
        first[u[i] - 1] = i;
    }

    /* 遍历邻接表 */
    /*
    for (int i = 0; i < n; i++) {
        int tmp = first[i];
        while (tmp != -1) {
            cout << u[tmp] << " -> " << v[tmp] << " = " << w[tmp] << endl;
            tmp = next[tmp];
        }
    }
    */

    fill_n(vis, n, 0);  // 0 表示未访问过，1 表示已访问

    fill_n(dis, n, imax);
    dis[s - 1] = 0;

    fill_n(pre, n, -1);
    pre[s - 1] = s - 1;

    // 初始化
    vis[s - 1] = 1;
    int tmp = first[s - 1];
    while (tmp != -1) {
        dis[v[tmp] - 1] = w[tmp];
        pre[v[tmp] - 1] = s - 1;
        tmp = next[tmp];
    }

    while (true) {
        // 寻找下一个起点
        int min = imax;
        int k = -1;
        for (int j = 0; j < n; j++) {
            if (!vis[j] && dis[j] < min) {
                min = dis[j];
                k = j;
            }
        }
        if (k == -1)    // 没有下一个起点则结束算法
            break;

        tmp = first[k];
        vis[k] = 1;
        while (tmp != -1) {
            if (!vis[v[tmp] - 1] && min + w[tmp] < dis[v[tmp] - 1]) {
                dis[v[tmp] - 1] = min + w[tmp];
                pre[v[tmp] - 1] = k;
            }
            tmp = next[tmp];
        }
    }

    // 打印结果
    for (int i = 0; i < n; i++) {
        if (dis[i] == imax) {
            cout << "no path to " << i+1 << endl;
            continue;
        }
        cout << "dis: " << dis[i] << "; path: " << i + 1 << " <- ";
        int p = i;
        while (pre[p] != s - 1 && pre[p] != -1) {
            cout << pre[p] + 1 << " <- ";
            p = pre[p];
        }
        cout << s << endl;
    }

    delete[] u;
    delete[] v;
    delete[] w;
    delete[] first;
    delete[] next;
    delete[] dis;
    delete[] pre;
    delete[] vis;

    return 0;
}
