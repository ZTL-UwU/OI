#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
struct data
{
    int v, w;
};
const int MAXN = 1e3;
vector<data> g[MAXN];
bool inque[MAXN];
int dis[MAXN];
inline void init()
{
    for (int i = 0; i < MAXN; i++)
        g[i].clear();
    memset(inque, 0, sizeof(inque));
    memset(dis, 127, sizeof(dis));
}
inline void SPFA()
{
    queue<int> q;
    q.push(1);
    dis[1] = 0;
    inque[1] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
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
    int t;
    cin >> t;
    while (t--)
    {
        init();
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            g[u].push_back((data){v, w});
        }
        SPFA();
        cout << dis[n] << "\n";
    }
    return 0;
}