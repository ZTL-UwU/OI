#include <iostream>
#include <regex>
#include <vector>

const int INF = 0x7fffffff;
const int MAX_N = 2e3 + 10;

struct node
{
    int v;
    int w;
};

std::vector<node> g[MAX_N];
int min_diff = INF;
bool find_smaller;
bool vis[MAX_N];
int n, m;

inline void dfs(int u, int max, int min, int ref)
{
    if (min != INF and (max - min >= ref or max - min >= min_diff))
        return;
    if (u == n)
    {
        min_diff = max - min;
        find_smaller = true;
        return;
    }

    for (auto v : g[u])
    {
        if (not vis[v.v])
        {
            vis[v.v] = true;
            dfs(v.v, std::max(max, v.w), std::min(min, v.w), ref);
            vis[v.v] = false;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m;

    int min_w = INF;
    int max_w = -INF;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        max_w = std::max(max_w, w);
        min_w = std::min(min_w, w);

        g[u].push_back((node){v, w});
        g[v].push_back((node){u, w});
    }

    int l = 0;
    int r = max_w - min_w;

    while (r - l > 1)
    {
        int mid = (r + l) / 2;

        find_smaller = false;
        dfs(1, -INF, INF, mid);

        if (find_smaller)
            r = min_diff;
        else
            l = mid;
    }

    std::cout << r;
    return 0;
}