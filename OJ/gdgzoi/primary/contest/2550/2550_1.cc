#include <iostream>
#include <stack>
#include <vector>

const int MOD = 1e9 + 7;

long long quick_pow(long long a, int n)
{
    long long ans = 1;
    while (n != 0)
    {
        if (n % 2 == 1)
            ans = (ans * a) % MOD;
        a = (a * a) % MOD;
        n /= 2;
    }

    return ans;
}

long long c(int n, int m)
{
    long long top = 1;
    long long bottom = 1;

    for (int i = n; i >= n - m + 1; i--)
        top = (top * i) % MOD;
    for (int i = m; i >= 1; i--)
        bottom = (bottom * i) % MOD;

    return top * quick_pow(bottom, MOD - 2) % MOD;
}

const int TABLE[] = {0, 1, 2, 3, 5, 9};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        int n, m;
        std::cin >> n >> m;
        if (n == m)
        {
            std::cout << "1\n";
            continue;
        }

        auto c_res = c(n, m) % MOD;

        std::stack<int> ans;
        while (c_res != 0)
        {
            ans.push((c_res - 1) % 5 + 1);
            c_res = (c_res - 1) / 5;
        }

        while (!ans.empty())
        {
            std::cout << TABLE[ans.top()];
            ans.pop();
        }
        std::cout << "\n";
    }

    return 0;
}