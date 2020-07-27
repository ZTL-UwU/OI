#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
struct node { int v, w; };
const int INF = 0x7fffffff;
const int MAXN = 1e5 + 100;
vector<node> t[MAXN];
int tt[32 * MAXN][2];
int maxn = -INF;
int x[MAXN];
int s = 1;
inline void insert(int k)
{
    int u = 1;
    for (int i = 31; i >= 0; i --)
    {
        bool tmp = (k & (1 << i)) ? 1 : 0;
        if (!tt[u][tmp]) tt[u][tmp] = ++ s;
        u = tt[u][tmp];
    }
}
inline int work(int k)
{
    int u = 1;
    int res = 0;
    for (int i = 31; i >= 0; i --)
    {
        bool tmp = (k & (1 << i)) ? 0 : 1;
        if (tt[u][tmp])
        {
            res = res * 2 + 1;
            u = tt[u][tmp];
        }
        else
        {
            res *= 2;
            u = tt[u][!tmp];            
        }
    }
    return res;
}
inline void dfs(int u, int fa)
{
    for (int i = 0; i < t[u].size(); ++ i)
    {
        int v = t[u][i].v;
        int w = t[u][i].w;
        if (v != fa)
        {
            x[v] = x[u] ^ w;
            dfs(v, u);
        }
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++ i)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        t[u].push_back((node){v, w});
        t[v].push_back((node){u, w});
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i ++) insert(x[i]);
    for (int i = 1; i <= n; i ++)
        maxn = max(maxn, max(x[i], work(x[i])));
    printf("%d", maxn);
    return 0;
}