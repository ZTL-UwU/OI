#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
const int MAXN = 100010;
vector<int> g[MAXN];
stack<int> st;
int pbc[MAXN];
int dfn[MAXN];
int low[MAXN];
int tt;
void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++ tt;
    for (int i = 0; i <g[u].size(); i ++)
    {
        int v = g[u][i];
        if (v == fa) continue;
        if (!dfn[v])
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u])
            {
                int p;
                do
                {
                    p = st.top();
                    st.pop();
                    pbc = 
                } while (p != v);

            }
        }
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
    }
    for (int i = 1; i <= n; i ++) if (!dfn[i]) tarjan(i, -1);
    return 0;
}