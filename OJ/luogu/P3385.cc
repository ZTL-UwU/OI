#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct data { int v, w; };
const int MAXN = 4e3;
vector<data> g[MAXN];
bool inque[MAXN];
int dis[MAXN];
int cnt[MAXN];
int n, m;
inline void init()
{
    for (int i = 0; i < MAXN; i++)
        g[i].clear();
    memset(inque, 0, sizeof(inque));
    memset(dis, 127, sizeof(dis));
    memset(cnt, 0, sizeof(cnt));
}
inline bool SPFA()
{
    queue<int> q;
    q.push(1);
    inque[1] = true;
    dis[1] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inque[u] = false;
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
                    inque[v] = false;
                    q.push(v);
                }
            }
        }
    }
    return true;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        init();
        cin >> n >> m;
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            if (w >= 0)
            {
                g[u].push_back((data){v, w});
                g[v].push_back((data){u, w});
            }
            else
                g[u].push_back((data){v, w});
        }
        if (SPFA())
            puts("NO");
        else
            puts("YES");
    }
    return 0;
}