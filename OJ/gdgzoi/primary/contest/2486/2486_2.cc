#include <cstddef>
#include <iostream>
#include <cstring>

const int MAX_N = 2e4 + 10;
const int MAX_ROUTE = 40 + 1;

int l_son[MAX_N];
int r_son[MAX_N];

int a[MAX_N];
int b[MAX_N];
int c[MAX_N];

long long int dp[MAX_N][MAX_ROUTE][MAX_ROUTE];

int n;

inline long long int dfs(int x, int y, int z)
{
    if (x >= n) // Village
        return 1LL * c[x - n + 1] * (a[x - n + 1] + y) * (b[x - n + 1] + z);

    if (dp[x][y][z] != dp[0][0][0]) // Visited
        return dp[x][y][z];

    dp[x][y][z] =
        std::min(dfs(l_son[x], y, z) + dfs(r_son[x], y, z + 1), dfs(l_son[x], y + 1, z) + dfs(r_son[x], y, z));

    return dp[x][y][z];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n;

    std::memset(dp, 60, sizeof(dp));

    for (int i = 1; i <= n - 1; i++)
    {
        std::cin >> l_son[i] >> r_son[i];

        l_son[i] = l_son[i] < 0 ? n - l_son[i] - 1 : l_son[i];
        r_son[i] = r_son[i] < 0 ? n - r_son[i] - 1 : r_son[i];
    }

    for (int i = 1; i <= n; i++)
        std::cin >> a[i] >> b[i] >> c[i];

    std::cout << dfs(1, 0, 0);
    return 0;
}