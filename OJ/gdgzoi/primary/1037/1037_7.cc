#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;
struct data
{
    int v, w;
};
vector<data> g[100000];
bool inque[100000];
int d[100000];
void spfa(int start)
{
    queue<int> q;
    q.push(start);
    inque[start] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inque[u] = false;
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            if (d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
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
    memset(d, 0x7f, sizeof(d));
    int n, s, e;
    cin >> n >> s >> e;
    for (int i = 0; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        if (v > e)
            v = e;
        v++;
        g[u].push_back((data){v, w});
    }
    for (int i = 1; i <= e + 1; i++)
    {
        g[i + 1].push_back((data){i, 0});
    }
    d[s] = 0;
    spfa(s);
    if (d[e + 1] == 2139062143)
        cout << -1;
    else
        cout << d[e + 1];
    return 0;
}