#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <string.h>
using namespace std;
const int MAXN = 200000;
int dfn[MAXN];
int low[MAXN];
int tt;
int col;
int color[MAXN];
int num[MAXN];
vector<int> g[MAXN];
stack<int> s;
int n, m;
bool used[MAXN];
void init()
{
    for (int i = 0; i < MAXN; i++)
        g[i].clear();
    while (!s.empty())
        s.pop();
    memset(used, 0, sizeof(used));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(num, 0, sizeof(num));
    memset(color, 0, sizeof(color));
    tt = 0;
    col = 0;
    n = 0;
    m = 0;
}
void tarjan(int u)
{
    dfn[u] = low[u] = ++tt;
    s.push(u);
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!color[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        ++col;
        int v = -1;
        do
        {
            v = s.top();
            s.pop();
            color[v] = col;
            num[col]++;
        } while (u != v);
    }
}
int main()
{
    while (1)
    {
        cin >> n >> m;
        if (!n && !m)
            return 0;
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
        }
        for (int i = 0; i <= n; i++)
            if (!dfn[i])
                tarjan(i);
        int maxn = -0x7fffffff;
        for (int i = 1; i <= col; i++)
            maxn = max(maxn, num[i]);
        if (maxn == n)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    return 0;
}
