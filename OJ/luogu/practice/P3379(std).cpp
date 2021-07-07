#include <bits/stdc++.h>
using namespace std;
int f[1100000];
int dep[1100000];
int pos[1100000];
vector<int> t[1100000];
int dck = 0;
int cnt = 0;
int dp[1100000][50];
void init()
{
    memset(dp, 127, sizeof(dp));
    for (int i = 1; i <= 1000000; i++)
    {
        dep[i] = 0;
        f[i] = 0;
        pos[i] = 0;
        t[i].clear();
    }
}
void dfs(int u, int d, int fa)
{
    ++cnt;
    pos[u] = cnt;
    f[cnt] = u;
    dep[cnt] = d;
    for (int i = 0; i < t[u].size(); i++)
    {
        int v = t[u][i];
        if (v == fa)
        {
            continue;
        }
        dfs(v, d + 1, u);
        ++cnt;
        f[cnt] = u;
        dep[cnt] = d;
    }
}
int rmq_init(int n)
{
    for (int i = 1; i <= cnt; i++)
    {
        dp[i][0] = i;
    }
    for (int j = 1; (1 << j) <= cnt; j++)
    {
        for (int i = 1; i + (1 << j) - 1 <= cnt; i++)
        {
            dp[i][j] =
                dep[dp[i][j - 1]] < dep[dp[i + (1 << (j - 1))][j - 1]] ? dp[i][j - 1] : dp[i + (1 << (j - 1))][j - 1];
        }
    }
}
int lca_request(int u, int v)
{
    int l = pos[u], r = pos[v];
    if (r < l)
    {
        swap(l, r);
    }
    int k = (int)log2(r - l + 1);
    return (dep[dp[l][k]] < dep[dp[r - (1 << k) + 1][k]] ? f[dp[l][k]] : f[dp[r - (1 << k) + 1][k]]);
}
int main()
{
    freopen("P3379.in", "r", stdin);
    freopen("P3379.ans", "w", stdout);
    init();
    int n, q, s;
    cin >> n >> q >> s;
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
    dfs(s, 1, 0);
    rmq_init(cnt);
    for (int i = 1; i <= q; i++)
    {
        int u, v;
        cin >> u >> v;
        cout << lca_request(u, v) << endl;
    }
}