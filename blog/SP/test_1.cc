#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct data
{
    int v, w;
};
const int MAXN = 1e5 + 10;
int dis[MAXN];
bool inque[MAXN];
vector<data> g[MAXN];
inline void spfa(int s)
{
    for (int i = 1; i <= MAXN; i++)
        dis[i] = 0x7fffffff;
    dis[s] = 0;
    queue<int> q;    // 创建队列
    q.push(s);       // 初始化队列
    inque[s] = true; // 记录 inque 状态
    int sum = 0;
    while (!q.empty())
    {
        int u = q.front();
        // sum -= dis[u];
        if (q.size() * dis[u] > sum)
        {
            q.push(u);
            sum += dis[u];
            continue;
        }
        q.pop();
        inque[u] = false;
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            if (dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                if (!inque[v])
                {
                    inque[v] = true;
                    q.push(v);
                    sum += dis[v];
                }
            }
        }
    }
}
int main()
{
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back((data){v, w});
    }
    spfa(s);
    printf("%d ", dis[t]);
    return 0;
}