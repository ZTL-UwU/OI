#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
const int MAXN = 1000100;
struct data { int u, v; };
vector<int> g[MAXN];
vector<data> e;
stack<int> st;
int color[MAXN];
int dfn[MAXN];
int low[MAXN];
int col;
int tt;
void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ tt;
    st.push(u);
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i];
        if (!dfn[v])
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else if (v != fa) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        col ++;
        int v;
        do
        {
            v = st.top();
            st.pop();
            color[v] = col;
        } while (u != v);
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i ++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        e.push_back((data){u, v});
    }
    for (int i = 1; i <= n; i ++) if (!dfn[i]) tarjan(i, -1);
    for (int i = 0; i < e.size(); i ++) if (color[e[i].u] != color[e[i].v]) cout << i + 1 << "\n";
    return 0;
}