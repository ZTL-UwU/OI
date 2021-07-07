#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>
using namespace std;
const int MAXN = 60000;
vector<int> g[MAXN];
int dfn[MAXN];
int low[MAXN];
int tt;
int col;
int color[MAXN];
stack<int> s;
int num[MAXN];
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
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, type;
        cin >> u >> v >> type;
        if (type == 1)
            g[u].push_back(v);
        if (type == 2)
        {
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    int maxn_place = 0;
    for (int i = 1; i <= col; i++)
        if (num[i] > num[maxn_place])
            maxn_place = i;
    cout << num[maxn_place] << endl;
    for (int i = 1; i <= n; i++)
    {
        if (color[i] == maxn_place)
            cout << i << " ";
    }
    return 0;
}
