#include <iostream>
#include <vector>

using i64 = long long;
const i64 MOD = 1000000007;
const i64 INV = 500000004;
const int MAX_LOG = 20;
const int MAX_N = 210;

std::vector<int> g[MAX_N];
int fa[MAX_N][MAX_LOG];
i64 dp[MAX_N][MAX_N];
int dep[MAX_N];

i64 q_pow(i64 a, int b)
{
    i64 res = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }

    return res;
}

void get_dp(int n)
{
    for (int i = 1; i <= n; i++)
        dp[0][i] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) * INV % MOD;
}

void dfs(int u, int f)
{
    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    for (int i = 1; i < MAX_LOG; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];

    for (auto v : g[u])
        if (v != f)
            dfs(v, u);
}

int LCA(int x, int y)
{
    if (dep[x] < dep[y])
        std::swap(x, y);

    for (int i = MAX_LOG - 1; i >= 0; i--)
        if (dep[x] - (1 << i) >= dep[y])
            x = fa[x][i];
    if (x == y)
        return x;

    for (int i = MAX_LOG - 1; i >= 0; i--)
        if (fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

int main()
{
    int n;
    std::cin >> n;
    get_dp(n);

    for (int i = 1; i < n; i++)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i++)
    {
        dfs(i, 0);
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k < j; k++)
            {
                const int lca = LCA(j, k);
                ans = (ans + dp[dep[j] - dep[lca]][dep[k] - dep[lca]]) % MOD;
            }
        }
    }

    std::cout << ans * q_pow(n, MOD - 2) % MOD;
    return 0;
}