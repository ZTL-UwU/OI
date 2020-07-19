#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
const int MAXN = 6000;
vector<int> g[MAXN];
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
    }
    for (int i = 1; i <= n; i ++) if (!dfn[i]) tarjan(i, -1);
    return 0;
}