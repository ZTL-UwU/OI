#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

const int MAXN = 1e4;
std::vector<int> a[MAXN];
std::vector<int> ans;
bool vis[MAXN];
int min[MAXN];
int fa[MAXN];

inline int find(int x)
{
    if (fa[x] == x)
        return x;

    fa[x] = find(fa[x]);
    return fa[x];
}

inline void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
    {
        fa[fx] = fy;
        min[fy] = std::min(min[fx], min[fy]);
    }
}

int main()
{
    for (int i = 0; i < MAXN; i++)
        fa[i] = i;

    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        std::cin >> min[i];

        int k;
        std::cin >> k;

        for (int j = 1; j <= k; j++)
        {
            int tmp;
            std::cin >> tmp;
            a[i].push_back(tmp);
        }
    }

    for (int i = 1; i <= m; i++)
        for (auto j : a[i])
            merge(i, j);

    for (int i = 1; i <= m; i++)
    {
        int f = find(i);
        if (!vis[f])
        {
            vis[f] = true;
            ans.push_back(min[f]);
        }
    }

    if (ans.size() <= n + 1)
    {
        std::cout << "AK";
        return 0;
    }

    std::sort(ans.begin(), ans.end());
    std::cout << ans[n + 1];
    return 0;
}