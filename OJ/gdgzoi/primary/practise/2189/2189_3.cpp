#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
const int MAXN = 100100;
struct data { int u, v; };
vector<int> g[MAXN];
stack<int> st;
int color[MAXN];
int dfn[MAXN];
int low[MAXN];
int col;
int tt;
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
        else if (!color[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
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
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i ++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
    }
    for (int i = 1; i <= n; i ++) if (!dfn[i]) tarjan(i);
    int q;
    cin >> q;
    for (int i = 0; i < q; i ++)
    {
        int u, v;
        cin >> u >> v;
        if (color[u] == color[v]) puts("1");
        else puts("0");
    }
    return 0;
}