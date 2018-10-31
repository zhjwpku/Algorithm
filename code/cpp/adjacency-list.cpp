/*
 * 邻接表的数组实现
 * Input:
 * 4 5
 * 1 4 9
 * 4 3 8
 * 1 2 5
 * 2 4 6
 * 1 3 7
 * */

#include <iostream>
#include <algorithm> 

using namespace std;

int main()
{
    int n;  // 节点数
    int m;  // 边数
    /*
     * u[i]、v[i]和w[i]表示第i条边是从第u[i]号顶点到v[i]号顶点（u[i]àv[i]），且权值为w[i]
     * */
    int *u = NULL;
    int *v = NULL;
    int *w = NULL;

    int *first = NULL;
    int *next = NULL;

    cin >> n >> m;

    u = new int[m];
    v = new int[m];
    w = new int[m];

    first = new int[n];
    next = new int[m];

    fill_n(first, n, -1);

    /* 初始化邻接表 */
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        /*
        if (first[u[i] - 1] == -1) {
            first[u[i] - 1] = i;
            next[i] = -1;
        } else {
            next[i] = first[u[i] - 1];
            first[u[i] - 1] = i;
        }
        */

        next[i] = first[u[i] - 1];
        first[u[i] - 1] = i;
    }

    /* 遍历邻接表 */
    for (int i = 0; i < n; i++) {
        int tmp = first[i];
        while (tmp != -1) {
            cout << u[tmp] << " -> " << v[tmp] << " = " << w[tmp] << endl;
            tmp = next[tmp];
        }
    }

    delete[] u;
    delete[] v;
    delete[] w;
    delete[] first;
    delete[] next;

    return 0;
}
