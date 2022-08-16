#include <cstdio>
#include <cstring>
#include <iostream>
int n, cnt;
int to[210], next[210], head[110];
int f[110][2], g[110][2];
// f摁,g不摁,0不亮,1亮
void dfs(int x, int fa)
{
    g[x][1] = f[x][0] = n + 1, f[x][1] = 1, g[x][0] = 0;
    for (int i = head[x]; i != -1; i = next[i])
    {
        if (to[i] == fa)
            continue;
        dfs(to[i], x);
        int f0 = f[x][0];
        int f1 = f[x][1];
        int g0 = g[x][0];
        int g1 = g[x][1];
        f[x][0] = std::min(f[x][1] + f[to[i]][0], f[x][0] + g[to[i]][0]);
        f[x][1] = std::min(f[x][0] + f[to[i]][0], f[x][1] + g[to[i]][0]);
        g[x][0] = std::min(g1 + f[to[i]][1], g0 + g[to[i]][1]);
        g[x][1] = std::min(g0 + f[to[i]][1], g1 + g[to[i]][1]);
    }
}
void add(int a, int b) { to[cnt] = b, next[cnt] = head[a], head[a] = cnt++; }
int main()
{
    while (1)
    {
        scanf("%d", &n), cnt = 0;
        if (!n)
            return 0;
        int i, a, b;
        memset(head, -1, sizeof(head));
        for (i = 1; i < n; i++)
            scanf("%d%d", &a, &b), add(a, b), add(b, a);
        dfs(1, 0);
        printf("%d\n", std::min(f[1][1], g[1][1]));
    }
}