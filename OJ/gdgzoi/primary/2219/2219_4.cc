#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct data
{
    int v;
    int w;
};
int n, a1, a2, an, b1, b2, bn, s, t;
const int INF = 0x7fffffff;
const int MAXN = 1e3;
vector<data> g[MAXN];
char mp[MAXN][MAXN];
int minn[MAXN];
int pre[MAXN];
inline int EK_bfs()
{
    for (int i = 0; i < MAXN; i++)
    {
        minn[i] = INF;
        pre[i] = -1;
    }
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            if (pre[v] == -1 && w)
            {
                minn[v] = min(minn[u], w);
                pre[v] = u;
                q.push(v);
            }
        }
    }
    if (pre[t] == -1)
        return -1;
    return minn[t];
}
inline int EK()
{
    int ans = 0;
    while (1)
    {
        int tmp = EK_bfs();
        if (tmp == -1)
            break;
        ans += tmp;
        int u = t;
        while (u != s)
        {
            for (int i = 0; i < g[pre[u]].size(); i++)
            {
                if (g[pre[u]][i].v == u)
                {
                    g[pre[u]][i].w -= tmp;
                    break;
                }
            }
            bool found = false;
            for (int i = 0; i < g[u].size(); i++)
            {
                if (g[u][i].v == pre[u])
                {
                    g[u][i].w += tmp;
                    found = true;
                    break;
                }
            }
            if (!found)
                g[u].push_back((data){pre[u], tmp});
            u = pre[u];
        }
    }
    return ans;
}
inline void add_edge(int u, int v, int w)
{
    g[u].push_back((data){v, w});
    g[v].push_back((data){u, 0});
}
inline void init()
{
    for (int i = 0; i < MAXN; i++)
        g[i].clear();
}
inline void build()
{
    init();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (mp[i][j] == 'N')
                add_edge(i, j, INF);
            else if (mp[i][j] == 'O')
                add_edge(i, j, 1);
        }
    }
}
int main()
{
    s = 0;
    t = 500;
    while (cin >> n >> a1 >> a2 >> an >> b1 >> b2 >> bn)
    {
        a1++;
        a2++;
        b1++;
        b2++;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> mp[i][j];
        build();
        add_edge(s, a1, an);
        add_edge(a2, t, an);
        add_edge(s, b1, bn);
        add_edge(b2, t, bn);
        if (EK() != an + bn)
        {
            cout << "No\n";
            continue;
        }
        build();
        add_edge(s, a2, an);
        add_edge(a1, t, an);
        add_edge(s, b2, bn);
        add_edge(b1, t, bn);
        if (EK() != an + bn)
            cout << "No\n";
        else
            cout << "Yes\n";
    }
    return 0;
}