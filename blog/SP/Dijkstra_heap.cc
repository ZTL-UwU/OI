#include <iostream>
#include <vector>
#include <queue>
struct node
{
    int v;
    int w;
};
struct data
{
    int dis;
    int num;
    bool operator>(const data x) const
    {
        if (this->dis != x.dis)
            return this->dis > x.dis;
        return this->num > x.num;
    }
};
using namespace std;
const int INF = 0x7fffffff;
const int MAXN = 1e5 + 10;
vector<node> g[MAXN];
bool vis[MAXN];
int dis[MAXN];
int n, m, s;
void Dijkstra()
{
    for (long long i = 0; i < MAXN; i++)
        dis[i] = INF;
    dis[s] = 0;
    priority_queue<data, vector<data>, greater<data>> pq;
    pq.push((data){0, s});
    while (!pq.empty())
    {
        int u = pq.top().num;
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
                pq.push((data){dis[v], v});
            }
        }
    }
}
int main()
{
    cin >> n >> m >> s;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back((node){v, w});
    }
    Dijkstra();
    for (int i = 1; i <= n; i++)
        cout << dis[i] << " ";
    return 0;
}