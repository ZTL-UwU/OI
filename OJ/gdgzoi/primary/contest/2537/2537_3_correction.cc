#include <iostream>
#include <vector>
#include <set>

struct node
{
    int v;
    int w;
};

const int MAX_ROUTE = 2e5 + 10;
const int MAX_N = 1e5 + 10;
const int MAX_LOG = 18;

std::vector<node> tree[MAX_N];
std::vector<int> depth;
std::vector<int> nodes;
int first[MAX_N];

long long num_depth[MAX_N];
int dfn[MAX_N];
int time_stamp;

std::set<int> set;
long long ans;

namespace ST
{
    int base[MAX_ROUTE][MAX_LOG];
    int log[MAX_ROUTE];

    void init()
    {
        log[0] = -1;
        for (int i = 1; i < MAX_ROUTE; i++)
            log[i] = log[i / 2] + 1;

        for (std::size_t i = 0; i < depth.size(); i++)
            base[i][0] = i;

        for (int i = 1; i < MAX_LOG; i++)
        {
            for (int j = 0; j + (1 << i) - 1 < depth.size(); j++)
            {
                const int l = base[j][i - 1];
                const int r = base[j + (1 << (i - 1))][i - 1];
                base[j][i] = depth[l] < depth[r] ? l : r;
            }
        }
    }

    int lca(int l_dfn, int r_dfn)
    {
        if (l_dfn == r_dfn)
            return l_dfn;

        int fl = first[l_dfn];
        int fr = first[r_dfn];
        if (fl > fr)
            std::swap(fl, fr);
        const int k = log[fr - fl + 1];

        const int l = base[fl][k];
        const int r = base[fr - (1 << k) + 1][k];
        return nodes[depth[l] < depth[r] ? l : r];
    }
}; // namespace ST

void dfs(int u, int dep, int fa)
{
    first[dfn[u]] = nodes.size();
    nodes.push_back(dfn[u]);
    depth.push_back(dep);

    for (auto v : tree[u])
    {
        if (v.v != fa)
        {
            dfn[v.v] = ++time_stamp;
            num_depth[dfn[v.v]] = num_depth[dfn[u]] + v.w;
            dfs(v.v, dep + 1, u);
            nodes.push_back(dfn[u]);
            depth.push_back(dep);
        }
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
        int u, v, w;
        std::cin >> u >> v >> w;

        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
    }

    dfs(1, 1, 0);
    ST::init();

    int q;
    std::cin >> q;
    for (int _i = 0; _i < q; _i++)
    {
        char op;
        std::cin >> op;

        const auto get_pre = [](std::set<int>::iterator it) -> std::set<int>::iterator
        { return it == set.begin() ? --set.end() : --it; };

        const auto get_nxt = [](std::set<int>::iterator it) -> std::set<int>::iterator
        { return it == --set.end() ? set.begin() : ++it; };

        const auto get_res = [](int x, int pre, int nxt) -> long long
        {
            return num_depth[x] + num_depth[pre] - 2 * num_depth[ST::lca(x, pre)] + num_depth[x] + num_depth[nxt]
                   - 2 * num_depth[ST::lca(x, nxt)]
                   - (num_depth[pre] + num_depth[nxt] - 2 * num_depth[ST::lca(pre, nxt)]);
        };

        if (op == '+')
        {
            int x;
            std::cin >> x;

            if (set.size() != 0)
            {
                auto nxt = set.lower_bound(dfn[x]);
                if (nxt == set.end())
                    nxt = set.begin();
                const auto pre = get_pre(nxt);

                ans += get_res(dfn[x], *pre, *nxt);
            }

            set.insert(dfn[x]);
        }
        else if (op == '-')
        {
            int x;
            std::cin >> x;

            const auto cur = set.find(dfn[x]);
            const auto pre = get_pre(cur);
            const auto nxt = get_nxt(cur);

            ans -= get_res(dfn[x], *pre, *nxt);

            set.erase(dfn[x]);
        }
        else if (op == '?')
            std::cout << ans / 2 << "\n";
    }

    return 0;
}
