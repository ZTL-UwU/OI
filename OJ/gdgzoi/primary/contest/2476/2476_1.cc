#include <iostream>
#include <cmath>

std::string str;
std::string ptr;
int ans = 0;
int n, m, k;

inline void dfs(int u)
{
    if (u == n)
    {
        if (str.find(ptr) != 18446744073709551615UL)
        {
            ans++;
            ans %= k;
        }
        return;
    }

    for (int i = 0; i <= 9; i++)
    {
        str[u] = '0' + i;
        dfs(u + 1);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m >> k >> ptr;

    for (int i = 0; i < n; i++)
        str += "0";

    dfs(0);
    std::cout << (int)(std::pow(10, n) - ans) % k;
    return 0;
}