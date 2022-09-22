#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

struct node
{
    int v;
    int w;
};

struct path
{
    int u;
    int v;
    int lca;
    int dis;
};

const int MAX_N = 3e5 + 10;
const int MAX_LOG = 30;

std::vector<node> g[MAX_N];
int fa[MAX_N][MAX_LOG];
int diff[MAX_N];
int pre[MAX_N];
int dep[MAX_N];
int wfa[MAX_N];
int lg[MAX_N];
path p[MAX_N];
int n, m;

void dfs1(int u)
{
    for (auto v : g[u])
    {
        if (v.v != fa[u][0])
        {
            fa[v.v][0] = u;
            dep[v.v] = dep[u] + 1;
            pre[v.v] = pre[u] + v.w;
            wfa[v.v] = v.w;
            for (int i = 1; i < MAX_LOG; i++)
                fa[v.v][i] = fa[fa[v.v][i - 1]][i - 1];
            dfs1(v.v);
        }
    }
}

int lca(int x, int y)
{
    if (dep[x] < dep[y])
        std::swap(x, y);
    while (dep[x] > dep[y])
        x = fa[x][lg[dep[x] - dep[y]] - 1];

    if (x == y)
        return x;
    for (int i = lg[dep[x]] - 1; i >= 0; i--)
    {
        if (fa[x][i] != fa[y][i])
        {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

void dfs2(int u)
{
    for (auto v : g[u])
    {
        if (v.v != fa[u][0])
        {
            dfs2(v.v);
            diff[u] += diff[v.v];
        }
    }
}

bool check(int key)
{
    int cnt = 0;
    int max = -1;
    std::memset(diff, 0, sizeof(diff));

    for (int i = 0; i < m; i++)
    {
        if (p[i].dis <= key)
            break;

        diff[p[i].u]++;
        diff[p[i].v]++;
        diff[p[i].lca] -= 2;
        cnt++;
    }

    dfs2(1);

    for (int i = 1; i <= n; i++)
        if (diff[i] == cnt)
            max = std::max(max, wfa[i]);
    return max >= p[0].dis - key;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m;

    int max_w = -1;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        max_w = std::max(max_w, w);
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    for (int i = 1; i <= n; i++)
        lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
    dfs1(1);

    int r = -1;
    for (int i = 0; i < m; i++)
    {
        std::cin >> p[i].u >> p[i].v;

        p[i].lca = lca(p[i].u, p[i].v);
        p[i].dis = pre[p[i].u] + pre[p[i].v] - 2 * pre[p[i].lca];
        r = std::max(r, p[i].dis);
    }

    std::sort(p, p + m, [](path p1, path p2) { return p1.dis > p2.dis; });

    int ans = 0;
    int l = r - max_w;
    while (l <= r)
    {
        const int mid = (l + r) / 2;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }

    std::cout << ans;
    return 0;
}