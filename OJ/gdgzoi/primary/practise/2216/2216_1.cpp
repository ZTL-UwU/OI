#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 100010;
const int INF = 0x7fffffff;
vector<int> g[MAXN];
queue<int> q;
int out[MAXN];
int val[MAXN];
int in[MAXN];
int w[MAXN];
int n, m;
void init()
{
    for (int i = 0; i < MAXN; i ++) val[i] = -INF;
    for (int i = 0; i < MAXN; i ++) g[i].clear();
    while (!q.empty()) q.pop();
    memset(out, 0, sizeof(out));
    memset(in, 0, sizeof(in));
    memset(w, 0, sizeof(w));
    n = m = 0;
}
void topo()
{
    for (int i = 1; i <= n; i ++) if (!in[i]) q.push(i), val[i] = w[i];
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < g[u].size(); i ++)
        {
            int v = g[u][i];
            val[v] = max(val[v], val[u] + w[v]);
            in[v] --;
            if (!in[v]) q.push(v);
        }
    }
}
int main()
{
    init();
    while (cin >> n >> m)
    {
        for (int i = 1; i <= n; i ++) cin >> w[i];
        for (int i = 0; i < m; i ++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            out[u] ++;
            in[v] ++;
        }
        topo();
        int ans = - INF;
        for (int i = 1; i <= n; i ++)
            if (!out[i]) ans = max(ans, val[i]);
        cout << ans << endl;
        init();
    }
    return 0;
}