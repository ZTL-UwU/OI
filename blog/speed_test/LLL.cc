#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct data { int v, w; };
const int MAXN = 1e5 + 10;
int dis[MAXN];
bool inque[MAXN];
vector<data> g[MAXN];
int n, m, s;
inline void spfa()
{
    for (int i = 1; i <= MAXN; i++)
        dis[i] = 0x7fffffff;
    dis[s] = 0;
    deque<int> dq;
    dq.push_back(1);
    inque[1] = true;
    int sum = 0;
    while (!dq.empty())
    {
        int u = dq.front();
        sum -= dis[u];
        dq.pop_front();
        if (dq.size() * dis[u] > sum)
        {
            dq.push_back(u);
            sum += dis[u];
            continue;
        }
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
                    // 若 dis[dq.front()] > dis[v] 将 v 由队首插入，否则从队尾插入
                    if (dq.empty() || dis[v] > dis[dq.front()])
                        dq.push_back(v);
                    else
                        dq.push_front(v);
                }
            }
        }
    }
}
int main()
{
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back((data){v, w});
    }
    spfa();
    for (int i = 1; i <= n; i++)
        printf("%d ", dis[i]);
    return 0;
}