#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

struct data
{
    int v;
    int w;
};

const int MAXN = 4e5;
std::vector<data> g[MAXN];
long long int dis1[MAXN];
long long int dis2[MAXN];
int start1, start2;

template <long long int dis[], int &start>
inline void dfs(int u, int fa = 0)
{
    for (auto v : g[u])
    {
        if (v.v != fa)
        {
            dis[v.v] = dis[u] + v.w;
            dfs<dis, start>(v.v, u);
        }
    }

    if (dis[u] > dis[start])
        start = u;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].push_back((data){v, w});
        g[v].push_back((data){u, w});
    }

    dfs<dis1, start1>(1);
    dfs<dis2, start2>(start1);
    dis1[start2] = 0;
    dfs<dis1, start1>(start2);

    long long int ans = -1;
    for (int i = 1; i <= n; i++)
    {
        if (i != start1 && i != start2)
        {
            long long int res = dis1[i] < dis2[i] ? dis1[i] + dis2[start2] : dis1[start1] + dis2[i];
            ans = std::max(ans, res);
        }
    }

    std::cout << ans;
    return 0;
}