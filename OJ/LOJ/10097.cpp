#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
const int MAXN = 30000;
vector<int> g[MAXN];
stack<int> s;
int color[MAXN];
int dfn[MAXN];
int low[MAXN];
int col;
int tt;
void tarjan(int u)
{
    dfn[u] = low[u] = ++ tt;
    s.push(u);
    for (int i = 0;i < g[u].size(); i ++)
    {
        int v = g[u][i];
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!color[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
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
    int n, m;
    cin >> n >> m;
    n *= 2;
    for (int i = 0; i < m; i ++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(((v - 1) ^ 1) + 1);
        g[v].push_back(((u - 1) ^ 1) + 1);
    }
    for (int i = 1; i <= n; i ++) if (!dfn[i]) tarjan(i);
    for (int i = 2; i <= n; i += 2)
    {
        if (color[i] == color[i - 1])
        {
            cout << "NIE";
            return 0;
        }
    }
    for (int i = 2; i <= n; i += 2)
    {
        if (color[i] < color[i - 1]) cout << i << '\n';
        else cout << i - 1 << "\n";
    }
    return 0;
}