#include <algorithm>
#include <iostream>
#include <cstring>

const int MAX_N = 2e5 + 10;
using i64 = long long;

bool vis[MAX_N];
int a[MAX_N];
int t[MAX_N];
int n, m;

i64 solve(int k)
{
    std::memset(vis, 0, sizeof(vis));
    int u = 1;
    vis[1] = true;
    t[1] = a[0];
    i64 ans = 0;

    for (int i = 1; i < n; i++)
    {
        if (vis[(u + k) % n])
            u = (u + k + 1) % n;
        else
            u = (u + k) % n;
        ans += a[i] * a[i - 1];
        t[u] = a[i];
        vis[u] = true;
    }
    for (int i = 1; i <= n; i++)
        std::cout << t[i] << " ";
    std::cout << "\n";

    return ans;
}

int main()
{
    std::cin >> n >> m;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    std::sort(a, a + n, std::greater<int>());

    for (int i = 0; i < m; i++)
    {
        int k;
        std::cin >> k;
        std::cout << solve(k) << "\n";
    }
    return 0;
}