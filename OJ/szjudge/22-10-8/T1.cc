#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>

const int MAX_N = 1e5 + 10;
using i64 = long long;

struct data
{
    i64 val;
    int l, r;
};

std::vector<data> pair;
bool vis[MAX_N];
i64 a[MAX_N];

int main()
{
    std::freopen("coin9.in", "r", stdin);
    int n, k;
    std::cin >> n >> k;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    for (int i = 0; i < n; i++)
    {
        if (i < n - k)
            pair.push_back({a[i] + a[i + k], i, i + k});
        if (i > k)
            pair.push_back({a[i] + a[i - k], i, i - k});
    }

    std::sort(pair.begin(), pair.end(), [](data d1, data d2) { return d1.val > d2.val; });

    i64 ans = 0;
    for (data i : pair)
    {
        if (!vis[i.l] && !vis[i.r])
        {
            ans += i.val;
            vis[i.l] = true;
            vis[i.r] = true;
        }
    }

    std::cout << ans;
    return 0;
}