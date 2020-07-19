#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
const int MAXN = 20010;
vector<int> g[MAXN];
vector<int> s[MAXN];
stack<int> st;
bool vis[MAXN];
int dfn[MAXN];
int low[MAXN];
int num[MAXN];
bool color[MAXN];
int col;
int tt;
int fa[MAXN];
int find(int u)
{
    if (fa[u] == u) return u;
    return fa[u] = find(fa[u]);
}
void merge(int u, int v)
{
    int fu = find(u), fv = find(v);
    fa[fu] = fv;
}
void dfs1(int u, int fa)
{
    for (int i = 0; i < s[u].size(); i ++)
    {
        int v = s[u][i];
        if (v != fa && !vis[v])
        {
            vis[v] = true;
            dfs1(v, u);
        }
    }
}
void tarjan(int u)
{
    dfn[u] = low[u] = ++ tt;
    st.push(u);
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i];
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(!color[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        int v;
        col ++;
        do
        {
            v = st.top();
            st.pop();
            color[v] = true;
            num[col] ++;
        } while (u != v);
    }
}
int main()
{
    for (int i = 0; i < MAXN; i ++) fa[i] = i;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i ++)
    {
        int u, v;
        char ch;
        cin >> u >> ch >> v;
        if (ch == '>') g[find(u)].push_back(find(v));
        else if(ch == '<') g[find(v)].push_back(find(u));
        else merge(u, v);
        s[u].push_back(v);
        s[v].push_back(u);
    }
    vis[0] = true;
    dfs1(0, -1);
    bool connected = true;
    for (int i = 0; i < n; i ++)
    {
        if (!vis[i])
        {
            connected = false;
            break;
        }
    }
    tarjan(0);
    int cc = col;
    for (int i = 1; i <= col; i ++)
        if (num[i] == 1) cc --;
    col = cc;
    if (col && !connected)
    {
        cout << "CONFLICT";
        return 0;
    }
    if (!connected)
    {
        cout << "UNCERTAIN";
        return 0;
    }
    if (col)
    {
        cout << "CONFLICT";
        return 0;
    }
    cout << "OK";
    return 0;
}