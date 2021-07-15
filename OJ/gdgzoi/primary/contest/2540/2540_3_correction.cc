#include <iostream>
#include <vector>

const int MAX_N = 3e5 + 10;
const int MOD = 998244353;
const int MAX_POW = 51;

std::vector<int> g[MAX_N];

unsigned long long depth_to_root[MAX_N][MAX_POW];
unsigned long long depth[MAX_N][MAX_POW];

namespace LCA
{
    const int MAX_ROUTE = 6e5 + 10;
    const int MAX_LOG = 21;

    int st[MAX_ROUTE][MAX_LOG];
    std::vector<int> depth;
    std::vector<int> id;
    int log[MAX_ROUTE];
    int first[MAX_N];

    void init()
    {
        log[0] = -1;
        for (int i = 1; i < MAX_ROUTE; i ++)
            log[i] = log[i / 2] + 1;

        for (std::size_t i = 0; i < id.size(); i++)
            st[i][0] = i;

        for (std::size_t i = 1; i < MAX_LOG; i++)
        {
            for (std::size_t j = 0; j + (1 << i) - 1 < id.size(); j++)
            {
                const int l = st[j][i - 1];
                const int r = st[j + (1 << (i - 1))][i - 1];
                st[j][i] = depth[l] < depth[r] ? l : r;
            }
        }
    }

    int query(int x, int y)
    {
        x = first[x];
        y = first[y];
        if (x > y)
            std::swap(x, y);

        const int k = log[y - x + 1];
        const int l = st[x][k];
        const int r = st[y - (1 << k) + 1][k];
        return id[depth[l] < depth[r] ? l : r];
    }
} // namespace LCA

long long mod_pow(long long a, int b)
{
    long long int ans = 1;
    for (int i = 0; i < b; i++)
    {
        ans = ans * a;
        ans %= MOD;
    }

    return ans;
}

void dfs1(int u, int fa)
{
    LCA::first[u] = LCA::id.size();
    LCA::depth.push_back(depth[u][1]);
    LCA::id.push_back(u);
    for (auto v : g[u])
    {
        if (v != fa)
        {
            depth[v][1] = depth[u][1] + 1;
            dfs1(v, u);
            LCA::depth.push_back(depth[u][1]);
            LCA::id.push_back(u);
        }
    }

    depth_to_root[u][1] = (depth_to_root[fa][1] + depth[u][1]) % MOD;
    for (int i = 2; i < MAX_POW; i++)
    {
        depth[u][i] = mod_pow(depth[u][1], i);
        depth_to_root[u][i] = (depth_to_root[fa][i] + depth[u][i]) % MOD;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    for (int _i = 0; _i < n - 1; _i++)
    {
        int u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs1(1, 0);
    LCA::init();

    // for (int i = 1; i <= n; i++)
    //     std::cout << depth[i][5] << ' ';
    // return 0;

    int q;
    std::cin >> q;
    for (int _i = 0; _i < q; _i++)
    {
        int x, y, k;
        std::cin >> x >> y >> k;

        std::cout << (MOD + (depth_to_root[x][k] + depth_to_root[y][k]) % MOD
                     - (2 * depth_to_root[LCA::query(x, y)][k]) % MOD) % MOD << "\n";
    }
    return 0;
}
