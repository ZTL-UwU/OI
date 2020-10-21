#include <iostream>

const int MAXN = 1e6 + 10;
int next[MAXN * 2];
int to[MAXN * 2];
int size[MAXN];
int head[MAXN];
int num[MAXN];
int total;

inline void add(int u, int v)
{
    total++;
    to[total] = v;
    next[total] = head[u];
    head[u] = total;
}

inline void dfs(int u, int fa)
{
    size[u] = 1;
    for (int i = head[u]; i != -1; i = next[i])
    {
        int v = to[i];
        if (v != fa)
        {
            dfs(v, u);
            size[u] += size[v];
        }
    }
    ++num[size[u]];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        head[i] = -1;
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    dfs(1, 0);

    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i << 1; j <= n; j += i)
            num[i] += num[j];
        if (i * num[i] == n)
            ++ans;
    }

    std::cout << ans;
    return 0;
}