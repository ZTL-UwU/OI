#include <iostream>
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

        int max_step = 0;
        for (int i = 1; i <= 20; i++)
        {
            const auto step = quick_pow(5, i);
            if (c_res > step)
                c_res -= step;
            else
            {
                max_step = i;
                break;
            }
        }

        for (int i = max_step - 1; i >= 0; i--)
        {
            const auto step = quick_pow(5, i);
            int k = 1;
            while (c_res > step)
            {
                c_res -= step;
                k++;
            }

            std::cout << TABLE[k];
        }

        std::cout << "\n";
    }

    return 0;
}