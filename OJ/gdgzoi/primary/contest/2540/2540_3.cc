#include <iostream>
#include <vector>

const int MAX_N = 3e5 + 10;
const int MOD = 998244353;

std::vector<int> g[MAX_N];
int n;

namespace TL
{
    int father[MAX_N];
    int depth[MAX_N];
    int size[MAX_N];
    int rank[MAX_N];
    int son[MAX_N];
    int top[MAX_N];
    int id[MAX_N];
} // namespace TL

long long mod_power(int a, int b)
{
    long long int ans = 1;
    for (int i = 0; i < b; i++)
    {
        ans = ans * a;
        ans %= MOD;
    }

    return ans;
}

template<const int pow>
class ST
{
private:
    int* tree = new int[MAX_N * 4];

    void push_up(int k)
    {
        const int ls = k * 2;
        const int rs = k * 2 + 1;

        tree[k] = (tree[ls] + tree[rs]) % MOD;
    }

public:
    void build(int l = 1, int r = n, int k = 1)
    {
        if (l == r)
        {
            tree[k] = mod_power(TL::size[TL::rank[l]], pow);
            return;
        }

        const int ls = k * 2;
        const int rs = k * 2 + 1;
        const int mid = (l + r) / 2;

        build(l, mid, ls);
        build(mid + 1, r, rs);
        push_up(k);
    }

    long long query(int l_tar, int r_tar, int l = 1, int r = n, int k = 1)
    {
        if (l_tar <= l && r <= r_tar)
            return tree[k];

        const int ls = k * 2;
        const int rs = k * 2 + 1;
        const int mid = (l + r) / 2;

        long long ans = 0;
        if (l_tar <= mid)
            ans = (ans + query(l_tar, r_tar, l, mid, ls)) % MOD;
        if (r_tar > mid)
            ans = (ans + query(l_tar, r_tar, mid + 1, r, rs)) % MOD;
        return ans;
    }
};

namespace TL
{
    void dfs1(int u)
    {
        depth[u] = depth[father[u]] + 1;
        size[u] = 1;

        for (auto v : g[u])
        {
            if (v != father[u])
            {
                father[v] = u;
                dfs1(v);

                size[u] += size[v];
                if (size[v] >= size[son[u]])
                    son[u] = v;
            }
        }
    }

    int new_id = 0;
    void dfs2(int u)
    {
        if (son[u])
        {
            id[son[u]] = ++new_id;
            top[son[u]] = top[u];
            rank[new_id] = u;
            dfs2(son[u]);
        }

        for (auto v : g[u])
        {
            if (v != father[u] && top[v] == 0)
            {
                id[v] = ++new_id;
                rank[new_id] = v;
                top[v] = v;
                dfs2(v);
            }
        }
    }

    long long route(int x, int y, int pow)
    {
        long long ans = 0;
        long long fx = top[x];
        long long fy = top[y];
        while (fx != fy)
        {
            if (depth[fx] < depth[fy])
            {
                std::swap(fx, fy);
                std::swap(x, y);
            }

            ans += 
        }
    }
} // namespace TL

int main()
{
    std::cin >> n;

    for (int _i = 0; _i < n - 1; _i++)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int q;
    std::cin >> q;

    TL::dfs1(1);
    TL::rank[1] = 1;
    TL::top[1] = 1;
    TL::id[1] = 1;
    TL::dfs2(1);

    for (int _i = 0; _i < q; _i++)
    {
        int x, y;
        std::cin >> x >> y;
    }
    return 0;
}
