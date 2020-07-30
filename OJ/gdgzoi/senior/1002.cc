#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct data { int v, w; };
const int INF = 0x7fffffff;
const int MAXN = 1e4 + 10;
vector<data> g[MAXN];
bool inque[MAXN];
int dis[MAXN];
int cnt[MAXN];
int n, m;
inline bool SPFA()
{
    for (int i = 0; i < MAXN; i++)
        dis[i] = -INF;
    queue<int> q;
    q.push(0);
    inque[0] = true;
    dis[0] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inque[u] = false;
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            if (dis[v] < dis[u] + w)
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
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, a, b;
        cin >> u >> v >> a >> b;
        g[u].push_back((data){v, -a});
        g[v].push_back((data){u, b});
    }
    if (!SPFA())
    {
        cout << "-1";
        return 0;
    }
    int maxn = -INF;
    for (int i = 0; i < n; i++)
        maxn = max(maxn, dis[i]);
    cout << maxn;
    return 0;
}