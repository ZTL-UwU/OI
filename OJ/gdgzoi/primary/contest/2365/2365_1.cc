#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>

const int MAXN = 5e5 + 10;
std::vector<int> tree[MAXN];
long long value[MAXN];
int size[MAXN];
int dfns[MAXN];
int dfn[MAXN];

long long tag[MAXN];
long long st[MAXN];

inline void build(int l, int r, int k)
{
    if (l == r)
    {
        st[k] = value[dfns[l]];
        return;
    }

    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;
    build(l, mid, ls);
    build(mid + 1, r, rs);

    st[k] = st[ls] + st[rs];
}

inline void update(int l, int r, int k, int x, int y, long long val)
{
    if (x <= l && r <= y)
    {
        tag[k] += val;
        return;
    }

    st[k] += (std::min(r, y) - std::max(l, x) + 1) * val;
    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;

    if (x <= mid)
        update(l, mid, ls, x, y, val);
    if (y > mid)
        update(mid + 1, r, rs, x, y, val);
}

inline long long query(int l, int r, int k, int x, int y)
{
    if (x <= l && r <= y)
        return st[k] + (r - l + 1) * tag[k];

    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;

    long long sum = (std::min(r, y) - std::max(l, x) + 1) * tag[k];
    if (x <= mid)
        sum += query(l, mid, ls, x, y);
    if (y > mid)
        sum += query(mid + 1, r, rs, x, y);
    return sum;
}

int time_stamp;
inline void dfs(int u)
{
    time_stamp++;
    dfn[u] = time_stamp;
    dfns[time_stamp] = u;

    size[u] = 1;
    for (auto v : tree[u])
    {
        dfs(v);
        size[u] += size[v];
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, q;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++)
        std::cin >> value[i];
    for (int i = 1; i <= n; i++)
    {
        int fa;
        std::cin >> fa;
        tree[fa].push_back(i);
    }

    dfs(1);

    build(1, n, 1);

    while (q--)
    {
        std::string token;
        std::cin >> token;

        if (token == "QUERY")
        {
            int u;
            std::cin >> u;
            std::cout << query(1, n, 1, dfn[u], dfn[u]) << "\n";
        }
        if (token == "OPERATE1")
        {
            int u;
            long long val;
            std::cin >> u >> val;
            update(1, n, 1, dfn[u], dfn[u], val);
        }
        if (token == "OPERATE2")
        {
            int u;
            long long val;
            std::cin >> u >> val;
            update(1, n, 1, dfn[u], dfn[u] + size[u] - 1, val);
        }
    }
    return 0;
}