#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
const int MAXN = 1100010;
vector<int> g[MAXN];
int f[MAXN][50];
int first[MAXN];
int deep[MAXN];
int num[MAXN];
int lg[MAXN];
int size;
void dfs(int u, int d, int fa)
{
    first[u] = ++size;
    deep[size] = d;
    num[size] = u;
    for (int i = 0; i < g[u].size(); ++i)
    {
        int v = g[u][i];
        if (v == fa)
            continue;
        dfs(v, d + 1, u);
        deep[++size] = d;
        num[size] = u;
    }
}
int main()
{
    lg[0] = -1;
    for (int i = 1; i < MAXN; ++i)
        lg[i] = lg[i / 2] + 1;
    int n, q, s;
    scanf("%d %d %d", &n, &q, &s);
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(s, 1, -1);
    for (int i = 1; i <= size; ++i)
        f[i][0] = i;
    for (int i = 1; i < 25; ++i)
        for (int j = 1; j + (1 << i) - 1 <= size; ++j)
            f[j][i] =
                deep[f[j][i - 1]] < deep[f[j + (1 << (i - 1))][i - 1]] ? f[j][i - 1] : f[j + (1 << (i - 1))][i - 1];
    for (int i = 0; i < q; ++i)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        int l = first[x], r = first[y];
        if (r < l)
            swap(l, r);
        int k = lg[r - l + 1];
        int res = num[deep[f[l][k]] < deep[f[r - (1 << k) + 1][k]] ? f[l][k] : f[r - (1 << k) + 1][k]];
        printf("%d\n", res);
    }
    return 0;
}