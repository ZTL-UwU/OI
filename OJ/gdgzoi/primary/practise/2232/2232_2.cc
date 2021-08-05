#include <iostream>
#include <climits>
#include <vector>

const int MAX_N = 1e5 + 10;
const int INF = INT_MAX;
const int ROOT = 1;

std::vector<int> g[MAX_N];
int value[MAX_N];
int root;
int n, q;

// Heavy Path Decomposition
namespace hpd
{
    int heavy_son[MAX_N];
    int father[MAX_N];
    int depth[MAX_N];
    int size[MAX_N];

    int time_stamp = 1;
    int rev_dfn[MAX_N];
    int dfn[MAX_N];
    int top[MAX_N];

    namespace st
    {
        const int MAX_K = 4 * MAX_N;
        int tree[MAX_K];
        int tag[MAX_K];

        void push_up(int k) { tree[k] = std::min(tree[k * 2], tree[k * 2 + 1]); }
        void push_down(int k)
        {
            if (tag[k] != 0)
            {
                tree[k] = tag[k];
                tree[k * 2] = tag[k];
                tree[k * 2 + 1] = tag[k];
                tag[k * 2] = tag[k];
                tag[k * 2 + 1] = tag[k];
                tag[k] = 0;
            }
        }

        void build(int l = 1, int r = n, int k = 1)
        {
            if (l == r)
            {
                tree[k] = value[rev_dfn[l]];
                return;
            }

            const int mid = (l + r) / 2;
            build(l, mid, k * 2);
            build(mid + 1, r, k * 2 + 1);

            push_up(k);
        }

        void update(int l_tar, int r_tar, int val, int l = 1, int r = n, int k = 1)
        {
            if (l_tar <= l && r <= r_tar)
            {
                tree[k] = val;
                tag[k] = val;
                return;
            }

            push_down(k);
            const int mid = (l + r) / 2;
            if (l_tar <= mid)
                update(l_tar, r_tar, val, l, mid, k * 2);
            if (r_tar > mid)
                update(l_tar, r_tar, val, mid + 1, r, k * 2 + 1);
            push_up(k);
        }

        int query(int l_tar, int r_tar, int l = 1, int r = n, int k = 1)
        {
            if (l_tar <= l && r <= r_tar)
                return tree[k];

            push_down(k);
            int min = INF;
            const int mid = (l + r) / 2;
            if (l_tar <= mid)
                min = std::min(min, query(l_tar, r_tar, l, mid, k * 2));
            if (r_tar > mid)
                min = std::min(min, query(l_tar, r_tar, mid + 1, r, k * 2 + 1));

            return min;
        }
    } // namespace st

    void dfs1(int u)
    {
        size[u] = 1;
        for (auto v : g[u])
        {
            if (v != father[u])
            {
                father[v] = u;
                depth[v] = depth[u] + 1;
                dfs1(v);

                size[u] += size[v];
                if (size[heavy_son[u]] < size[v])
                    heavy_son[u] = v;
            }
        }
    }

    void dfs2(int u)
    {
        if (heavy_son[u] != 0)
        {
            dfn[heavy_son[u]] = ++time_stamp;
            rev_dfn[time_stamp] = heavy_son[u];
            top[heavy_son[u]] = top[u];
            dfs2(heavy_son[u]);
        }

        for (auto v : g[u])
        {
            if (v != father[u] && v != heavy_son[u])
            {
                dfn[v] = ++time_stamp;
                rev_dfn[time_stamp] = v;
                top[v] = v;
                dfs2(v);
            }
        }
    }

    void init()
    {
        depth[ROOT] = 1;
        dfs1(ROOT);
        dfn[ROOT] = 1;
        rev_dfn[1] = ROOT;
        top[ROOT] = ROOT;
        dfs2(ROOT);
        st::build();
    }

    void route_update(int x, int y, int val)
    {
        while (top[x] != top[y])
        {
            if (depth[top[x]] < depth[top[y]])
                std::swap(x, y);

            st::update(dfn[top[x]], dfn[x], val);
            x = father[top[x]];
        }

        if (depth[x] < depth[y])
            std::swap(x, y);
        st::update(dfn[y], dfn[x], val);
    }
} // namespace hpd

// Quick Father
namespace qfa
{
    const int MAX_LOG = 25;
    int bin_father[MAX_N][MAX_LOG];
    int lg[MAX_N];

    void dfs(int u)
    {
        bin_father[u][0] = hpd::father[u];
        for (int i = 1; i <= lg[n] + 1; i++)
        {
            bin_father[u][i] = bin_father[bin_father[u][i - 1]][i - 1];
            if (!bin_father[u][i])
                break;
        }

        for (auto v : g[u])
            if (v != hpd::father[u])
                dfs(v);
    }

    void init()
    {
        lg[0] = -1;
        for (int i = 1; i < MAX_N; i++)
            lg[i] = lg[i / 2] + 1;

        dfs(ROOT);
    }

    int get_father(int x, int mult)
    {
        for (int i = lg[n] + 1; i >= 0; i--)
        {
            if (mult >= (1 << i))
            {
                x = bin_father[x][i];
                mult -= (1 << i);
            }
        }
        return x;
    }
} // namespace qfa

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> q;

    for (int _i = 0; _i < n - 1; _i++)
    {
        int u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
        std::cin >> value[i];

    hpd::init();
    qfa::init();

    std::cin >> root;
    for (int _i = 0; _i < q; _i++)
    {
        int op;
        std::cin >> op;

        if (op == 1)
            std::cin >> root;
        else if (op == 2)
        {
            int x, y, val;
            std::cin >> x >> y >> val;
            hpd::route_update(x, y, val);
        }
        else if (op == 3)
        {
            int x;
            std::cin >> x;

            int y = 0;
            if (x == root)
                std::cout << hpd::st::tree[1];
            else if (hpd::depth[x] < hpd::depth[root]
                     && hpd::father[y = qfa::get_father(root, hpd::depth[root] - hpd::depth[x] - 1)] == x)
            {
                std::cout << std::min(hpd::dfn[y] + hpd::size[y] <= n ? hpd::st::query(hpd::dfn[y] + hpd::size[y], n) :
                                                                        INF,
                                      hpd::st::query(1, hpd::dfn[y] - 1));
            }
            else
                std::cout << hpd::st::query(hpd::dfn[x], hpd::dfn[x] + hpd::size[x] - 1);

            std::cout << "\n";
        }
    }

    return 0;
}
