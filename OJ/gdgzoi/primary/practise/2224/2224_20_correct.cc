#include <unordered_set>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

const int MAX_N = 1e5 + 10;

std::unordered_set<int> s;
std::vector<int> t[MAX_N];
bool vis[MAX_N];
int size[MAX_N];
int val[MAX_N];

void factorize(int num)
{
    for (int i = 2; i <= std::sqrt(num); i++)
    {
        if (num % i == 0)
        {
            s.insert(i);
            while (num % i == 0)
                num /= i;
        }
    }

    if (num > 1)
        s.insert(num);
}

int dfs(int u)
{
    vis[u] = true;
    int rk1 = 0;
    int rk2 = 0;

    for (auto v : t[u])
    {
        if (!vis[v])
        {
            dfs(v);
            if (size[v] > rk1)
            {
                rk2 = rk1;
                rk1 = size[v];
            }
            else if (size[v] > rk2)
                rk2 = size[v];
        }
    }

    size[u] = rk1 + 1;
    return rk1 + rk2 + 1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    for (int _i = 0; _i < n - 1; _i++)
    {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;

        t[u].push_back(v);
        t[v].push_back(u);
    }

    for (int i = 0; i < n; i++)
    {
        std::cin >> val[i];
        factorize(val[i]);
    }

    int ans = -1;
    for (auto factor : s)
    {
        std::memset(vis, false, sizeof(vis));
        for (int i = 0; i < n; i++)
            if (val[i] % factor != 0)
                vis[i] = true;

        for (int i = 0; i < n; i++)
            if (!vis[i])
                ans = std::max(ans, dfs(i));
    }

    std::cout << ans;
    return 0;
}
