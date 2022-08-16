#include <algorithm>
#include <iostream>
#include <vector>

using pii = std::pair<int, int>;
const int MAX_N = 2e5 + 10;
const int MAX_M = MAX_N;
const int MAX_LOG = 25;

std::vector<int> g[MAX_N];

int fa[MAX_N][MAX_LOG];
int depth[MAX_N];
int d[MAX_N][2];
bool del[MAX_N];
int ufa[MAX_N];
int ans[MAX_M];
int dis[MAX_N];
int lg[MAX_N];
pii e[MAX_N];
pii q[MAX_M];

void init(int n)
{
    for (int i = 1; i < MAX_N; i++)
    {
        ufa[i] = i;
        d[i][0] = i;
        d[i][1] = i;
    }

    for (int i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;
}

int lca(int x, int y)
{
    if (depth[x] < depth[y])
        std::swap(x, y);

    while (depth[x] > depth[y])
        x = fa[x][lg[depth[x] - depth[y]]];

    if (x == y)
        return x;

    for (int i = lg[depth[x] - 1]; i >= 0; i--)
    {
        if (fa[x][i] != fa[y][i] && (1 << i) < depth[x])
        {
            x = fa[x][i];
            y = fa[y][i];
        }
    }

    return fa[x][0];
}

int get_dis(int x, int y) { return depth[x] + depth[y] - depth[lca(x, y)] * 2; }

void dfs(int u, int f)
{
    depth[u] = depth[f] + 1;

    fa[u][0] = f;
    for (int i = 1; (1 << i) < depth[u]; i++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];

    for (auto v : g[u])
        if (v != f)
            dfs(v, u);
}

int find(int x)
{
    if (ufa[x] == x)
        return x;
    return ufa[x] = find(ufa[x]);
}

void merge(int x, int y)
{
    const int fx = find(x);
    const int fy = find(y);
    ufa[fx] = fy;

    int max_d = dis[fx];
    int max_d0 = d[fx][0];
    int max_d1 = d[fx][1];

    if (max_d < dis[fy])
    {
        max_d = dis[fy];
        max_d0 = d[fy][0];
        max_d1 = d[fy][1];
    }

    const int d1[] = {0, 0, 1, 1};
    const int d2[] = {0, 1, 0, 1};

    for (int i = 0; i < 4; ++i)
    {
        const int v = get_dis(d[fx][d1[i]], d[fy][d2[i]]);

        if (max_d < v)
        {
            max_d = v;
            max_d0 = d[fx][d1[i]];
            max_d1 = d[fy][d2[i]];
        }
    }

    dis[fy] = max_d;
    d[fy][0] = max_d0;
    d[fy][1] = max_d1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    init(n);

    for (int i = 1; i < n; i++)
    {
        std::cin >> e[i].first >> e[i].second;

        g[e[i].first].emplace_back(e[i].second);
        g[e[i].second].emplace_back(e[i].first);
    }

    dfs(1, 0);

    for (int i = 1; i <= m; i++)
    {
        std::cin >> q[i].first >> q[i].second;
        if (q[i].first == 1)
            del[q[i].second] = true;
    }

    for (int i = 1; i < n; i++)
        if (!del[i])
            merge(e[i].first, e[i].second);

    for (int i = m; i >= 1; i--)
    {
        if (q[i].first == 2)
        {
            const int root = find(q[i].second);
            ans[i] = std::max(
                {get_dis(q[i].second, d[root][0]), get_dis(q[i].second, d[root][1]), get_dis(q[i].second, root)});
        }
        else
            merge(e[q[i].second].first, e[q[i].second].second);
    }

    for (int i = 1; i <= m; i++)
        if (q[i].first == 2)
            std::cout << ans[i] << "\n";
    return 0;
}