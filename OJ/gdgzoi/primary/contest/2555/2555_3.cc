#include <iostream>
#include <vector>

const int MAX_N = 8e5 + 10;
const int ROOT = 1;

std::vector<int> g[MAX_N];

int time_stamp = 1;
int size[MAX_N];
int dfn[MAX_N];
int son[MAX_N];
int fa[MAX_N];
int n, q;

void dfs1(int u)
{
    size[u] = 1;

    for (auto v : g[u])
    {
        dfs1(v);
        size[u] += size[v];

        if (size[v] > size[son[u]])
            son[u] = v;
    }
}

void dfs2(int u)
{
    if (son[u])
    {
        dfn[son[u]] = ++time_stamp;
        dfs2(son[u]);
    }

    for (auto v : g[u])
    {
        if (v != son[u])
        {
            dfn[v] = ++time_stamp;
            dfs2(v);
        }
    }
}

bool org[MAX_N];
int sit[MAX_N];

int lowbit(int x) { return x & -x; }

void update(int x)
{
    int delta = 1;
    if (org[x])
        delta = -1;
    org[x] += delta;

    while (x <= n)
    {
        sit[x] += delta;
        x += lowbit(x);
    }
}

int query_base(int x)
{
    int res = 0;
    while (x > 0)
    {
        res += sit[x];
        x -= lowbit(x);
    }

    return res;
}

bool query(int x) { return query_base(dfn[x] + size[x] - 1) - query_base(dfn[x] - 1); }

int solve(int x)
{
    if (query(x))
        return x;

    int u = fa[x];
    while (u != 0)
    {
        if (query(u))
            return u;
        u = fa[u];
    }

    return 0;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> q;

    for (int i = ROOT + 1; i <= n; i++)
    {
        std::cin >> fa[i];
        g[fa[i]].emplace_back(i);
    }

    dfs1(ROOT);
    dfn[ROOT] = 1;
    dfs2(ROOT);

    for (int _i = 0; _i < q; _i++)
    {
        int q_tmp;
        std::cin >> q_tmp;

        if (q_tmp > 0)
            update(dfn[q_tmp]);
        else
            std::cout << solve(-q_tmp) << "\n";
    }

    return 0;
}
