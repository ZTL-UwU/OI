#include <iostream>
#include <cstdio>
#include <string.h>
#include <vector>
#include <stack>
using namespace std;
const int MAXN = 2000100;
vector<int> g[MAXN];
stack<int> s;
int color[MAXN];
int dfn[MAXN];
int low[MAXN];
int n, m;
int col;
int tt;
void tarjan(int u)
{
    low[u] = dfn[u] = ++tt;
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
        int v;
        col++;
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
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int u, v, a, b;
        scanf("%d%d%d%d", &u, &a, &v, &b);
        g[u + n * (1 - a)].push_back(v + n * b);
        g[v + n * (1 - b)].push_back(u + n * a);
    }
    for (int i = 1; i <= n * 2; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= 2 * n; i++)
    {
        cout << color[i] << " ";
    }
    cout << "\n";
    for (int i = 1; i <= n; i++)
    {
        if (color[i] == color[i + n])
        {
            printf("IMPOSSIBLE\n");
            return 0;
        }
    }
    printf("POSSIBLE\n");
    for (int i = 1; i <= n; i++)
        printf("%d ", (color[i] > color[i + n]));
    printf("\n");
    return 0;
}