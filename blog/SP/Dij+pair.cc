#include <iostream>
#include <vector>
#include <queue>
struct node
{
    int v;
    int w;
};
using namespace std;
const int INF = 0x7fffffff;
const int MAX = 1e5 + 10;
vector<node> g[MAX];
bool vis[MAX];
int dis[MAX];
int n, m, s;
inline void Dijkstra()
{
    for (int i = 0; i < MAX; i++)
        dis[i] = INF;
    dis[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, s));
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            if (!vis[v] && dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                pq.push(make_pair(dis[v], v));
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
        g[u].push_back((node){v, w});
    }
    Dijkstra();
    for (int i = 1; i <= n; i++)
        printf("%d ", dis[i]);
    return 0;
}