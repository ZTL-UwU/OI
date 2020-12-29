#include <bits/stdc++.h>
#include <dbg.h>
#define MAXN 200000
using namespace std;
int n, m, s;
struct pos
{
    int x, y, id;
} p[MAXN + 5];
struct node
{
    int targ, dis;
    friend bool operator<(const node a, const node b) { return a.dis > b.dis; }
};
int dist[MAXN + 5];
bool vis[MAXN + 5];
vector<node> g[MAXN + 5];
int x[MAXN + 5], y[MAXN + 5];
priority_queue<node> q;
void dijkstra(int s)
{
    memset(dist, 127, sizeof(dist));
    dist[s] = 0;
    q.push((node){s, 0});
    while (!q.empty())
    {
        int u = q.top().targ;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].targ, w = g[u][i].dis;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                if (!vis[v])
                    q.push((node){v, dist[v]});
            }
        }
    }
}
bool cmp1(pos a, pos b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
bool cmp2(pos a, pos b)
{
    if (a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &p[i].x, &p[i].y);
        p[i].id = i;
    }
    sort(p + 1, p + n + 1, cmp1);
    for (int i = 1; i < n; i++)
    {
        int u = p[i].id, v = p[i + 1].id;
        int w = min(abs(p[i].x - p[i + 1].x), abs(p[i].y - p[i + 1].y));
        g[u].push_back((node){v, w});
        g[v].push_back((node){u, w});
    }
    sort(p + 1, p + n + 1, cmp2);
    for (int i = 1; i < n; i++)
    {
        int u = p[i].id, v = p[i + 1].id;
        int w = min(abs(p[i].x - p[i + 1].x), abs(p[i].y - p[i + 1].y));
        g[u].push_back((node){v, w});
        g[v].push_back((node){u, w});
    }

    for (int i = 1; i <= n; i++)
    {
        for (auto v : g[i])
            std::cout << "{" << v.targ << ":" << v.dis << "} ";
        std::cout << "\n";
    }

    dijkstra(1);
    printf("%d", dist[n]);
}