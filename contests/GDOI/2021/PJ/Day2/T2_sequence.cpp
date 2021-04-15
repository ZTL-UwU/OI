#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

const int MAX_M = 1e6 + 10;

int m, mod, ans;
std::vector<int> num;

int pow_2(const int n)
{
    int ans = 1;
    for (int i = 0; i < n; i++)
        ans = (ans * 2) % mod;

    return ans;
}

inline int c(const int a, const int b)
{
    int up = 1;
    int down = 1;
    for (int i = a; i >= a - b + 1; i--)
        up *= i;
    for (int i = b; i >= 1; i--)
        down *= i;

    return up / down;
}

void dfs(const int u)
{
    if (num.size() >= 4)
    {
        int xor_sum = num.back();
        for (int i = 1; i < 4; i++)
            xor_sum = xor_sum xor num[num.size() - 1 - i];

        if (xor_sum == 0)
        {
            ans -= pow_2(m - u);
            return;
        }
    }

    for (int i = u + 1; i <= m; i++)
    {
        num.push_back(i);
        dfs(i);
        num.pop_back();
    }
}

int main()
{
    std::freopen("sequence.in", "r", stdin);
    std::freopen("sequence.out", "w", stdout);

    std::scanf("%d %d", &m, &mod);

    ans = pow_2(m + 1) - 1;

    for (int i = 0; i <= m; i++)
    {
        num.push_back(i);
        dfs(i);
        num.pop_back();
    }

    std::printf("%d", ans % mod);
    return 0;
}