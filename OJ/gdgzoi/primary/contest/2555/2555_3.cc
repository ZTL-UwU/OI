#include <iostream>
#include <vector>

const int MAX_N = 8e5 + 10;
const int MAX_LOG = 21;
const int ROOT = 1;

std::vector<int> g[MAX_N];

int fa[MAX_N][MAX_LOG];
int size[MAX_N];
int dfn[MAX_N];

int n, time_stamp;

void dfs(const int u)
{
    size[u] = 1;
    dfn[u] = ++time_stamp;

    for (const auto v : g[u])
    {
        dfs(v);
        size[u] += size[v];
    }
}

bool org[MAX_N];
int sit[MAX_N];

int lowbit(const int x) { return x & -x; }

void update(int x)
{
    const int delta = org[x] ? -1 : 1;
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

bool query(const int x) { return query_base(dfn[x] + size[x] - 1) - query_base(dfn[x] - 1); }

int solve(const int x)
{
    if (query(x))
        return x;

    int u = x;
    int last_log = MAX_LOG;
    bool flag = true;
    while (!query(fa[u][0]))
    {
        flag = true;
        for (int i = last_log - 1; i >= 0; i--)
        {
            if (fa[u][i] != 0 && !query(fa[u][i]))
            {
                flag = false;
                u = fa[u][i];
                last_log = i;
                break;
            }
        }

        if (flag)
            return 0;
    }

    return fa[u][0];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int q;
    std::cin >> n >> q;

    for (int i = ROOT + 1; i <= n; i++)
    {
        std::cin >> fa[i][0];
        g[fa[i][0]].emplace_back(i);
    }

    for (int i = 1; i < MAX_LOG; i++)
        for (int j = 2; j <= n; j++)
            fa[j][i] = fa[fa[j][i - 1]][i - 1];

    dfs(ROOT);

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
