#include <stdio.h>
#include <iostream>
using namespace std;
const int N = 1000005;
int n, i, j, x, y, ans, f[N], p[N];
int tot, head[N], Next[N << 1], to[N << 1];
inline void add(int u, int v)
{
    tot++;
    to[tot] = v;
    Next[tot] = head[u];
    head[u] = tot;
}
void dfs(int x, int pre)
{
    f[x] = 1;
    for (int i = head[x]; i != -1; i = Next[i])
        if (to[i] != pre)
        {
            dfs(to[i], x);
            f[x] += f[to[i]];
        }
    p[f[x]]++;
}
int main()
{
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        head[i] = -1;
    for (i = 1; i < n; i++)
    {
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dfs(1, 0);
    for (i = 1; i <= n; i++)
    {
        for (j = i << 1; j <= n; j += i)
            p[i] += p[j];
        if (i * p[i] == n)
            ans++;
    }
    cout << ans;
    return 0;
}