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
int cnt[MAXN];
bool inque[MAXN];
vector<data> g[MAXN];
int n, m, s, R, val;
inline void spfa()
{
    for (int i = 1; i <= MAXN; i++)
        dis[i] = 0x7fffffff;
    dis[s] = 0;
    deque<int> q;
    q.push_back(s);
    inque[s] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop_front();
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
                    if (cnt[v] && cnt[v] < R)
                    {
                        q.push_front(v);
                        ++cnt[v];
                    }
                    else
                    {
                        if (q.size() == 0)
                            q.push_back(v);
                        else if (dis[*(q.begin())] >= dis[v] - val)
                            q.push_front(v);
                        else
                            q.push_back(v);
                        if (!cnt[v])
                            cnt[v] = 1;
                    }
                }
            }
        }
    }
}
int main()
{
    R = 200, val = 10;
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