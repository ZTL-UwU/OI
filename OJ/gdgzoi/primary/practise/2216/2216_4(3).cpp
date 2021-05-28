#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
const int MAXN = 20010;
int fa[MAXN];
int find(int u)
{
    if (fa[u] == u)
        return u;
    return fa[u] = find(fa[u]);
}
void merge(int u, int v)
{
    int fu = find(u), fv = find(v);
    fa[fu] = fv;
}
vector<int> g[MAXN];
vector<int> s[MAXN];
bool vis1[MAXN];
bool vis2[MAXN];
bool con1;
void dfs1(int u)
{
    if (con1)
        return;
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (vis1[v])
        {
            con1 = true;
            return;
        }
        vis1[v] = true;
        dfs1(v);
    }
}
void dfs2(int u, int fa)
{
    for (int i = 0; i < s[u].size(); i++)
    {
        int v = g[u][i];
        if (v != fa && !vis2[v])
        {
            vis2[v] = true;
            dfs2(v, u);
        }
    }
}
int main()
{
    for (int i = 0; i < MAXN; i++)
        fa[i] = i;
    int n, m, u, v;
    char ch;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> ch >> v;
        if (ch == '>')
            g[find(u)].push_back(find(v)), s[find(u)].push_back(find(v)), s[find(v)].push_back(find(u));
        else if (ch == '<')
            g[find(v)].push_back(find(u)), s[find(u)].push_back(find(v)), s[find(v)].push_back(find(u));
        else
            merge(u, v);
    }
    dfs1(0);
    dfs2(0, -1);

    return 0;
}