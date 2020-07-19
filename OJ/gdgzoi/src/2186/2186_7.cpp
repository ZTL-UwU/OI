#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
const int MAXN = 2000;
vector<int> g[MAXN];
stack<int> s;
int color[MAXN];
int dfn[MAXN];
int low[MAXN];
int n, m;
int col;
int tt;
void init()
{
    for (int i = 0; i < MAXN; i ++) g[i].clear();
    while (!s.empty()) s.pop();
    memset(color, 0, sizeof(color));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    n = m = col = tt = 0;
}
void tarjan(int u)
{
    dfn[u] = low[u] = ++ tt;
    s.push(u);
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i];
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!color[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        int v;
        col ++;
        do
        {
            v = s.top();
            s.pop();
            color[v] = col;
        } while (u != v);
    }
}
int main()
{
    int t;
    cin >> t;
    while (t --)
    {
        init();
        cin >> n >> m;
        getchar();
        for (int i = 0; i < m; i ++)
        {
            int u, v, va, vb;
            char a, b;
            a = getchar();
            cin >> u;
            getchar();
            b = getchar();
            cin >> v;
            if (a == 'm') va = 0;
            else va = 1;
            if (b == 'm') vb = 0;
            else vb = 1;
            getchar();
            g[u + n * (1 - va)].push_back(v + n * vb);
            g[v + n * (1 - vb)].push_back(u + n * va);
        }
        for (int i = 1; i <= n; i ++) if (!dfn[i]) tarjan(i);
        bool flag = true;
        for (int i = 1; i <= n; i ++)
        {
            if (color[i] == color[i + n])
            {
                cout << "BAD\n";
                flag = false;
                break;
            }
        }
        if (flag) cout << "GOOD\n";
    }
    return 0;
}