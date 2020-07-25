#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
struct data { int v, w; };
const int MAXN = 1e5;
vector<data> g[MAXN];
bool inque[MAXN];
int dis[MAXN];
void SPFA()
{
    memset(dis, 127, sizeof(dis));
    dis[1] = 0;
    queue<int> q;
    q.push(1);
    inque[1] = true;
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
                if (!inque[v])
                {
                    inque[v] = true;
                    q.push(v);
                }
            }
        }
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back((data){v, w});
    }
    SPFA();
    cout << dis[n];
    return 0;
}