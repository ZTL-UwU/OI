#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct data
{
    int v, w;
};
const int INF = 0x7fffffff;
const int MAXN = 2e3;
vector<data> g[MAXN];
bool inque[MAXN];
bool vis[MAXN];
int dis[MAXN];
int cnt[MAXN];
int n, m;
inline bool SPFA(int s)
{
    for (int i = 0; i < MAXN; i++)
        dis[i] = INF;
    queue<int> q;
    q.push(s);
    inque[s] = true;
    dis[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inque[u] = false;
        vis[u] = true;
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] > n)
                    return false;
                if (!inque[v])
                {
                    inque[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return true;
}
int main()
{
    int s;
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back((data){v, w});
    }
    bool flag = true;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            flag &= SPFA(i);
    if (!flag)
        puts("-1");
    else
    {
        SPFA(s);
        for (int i = 1; i <= n; i++)
        {
            if (dis[i] == INF)
                puts("NoPath");
            else
                cout << dis[i] << "\n";
        }
    }
    return 0;
}