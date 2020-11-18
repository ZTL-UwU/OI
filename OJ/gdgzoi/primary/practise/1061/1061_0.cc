#include <iostream>
#include <cstdio>

const int MOD = 5e6 + 11;

int quick_power(long long int a, int n)
{
    long long int ans = 1;

    while (n != 0)
    {
        if (n % 2 == 1)
            ans = (ans * a) % MOD;

        a = (a * a) % MOD;
        n >>= 1;
    }

    return ans;
}

inline long long int c(int n, int m)
{
    long long int top = 1;
    for (int i = n; i >= n - m + 1; i--)
        top = (top * i) % MOD;

    long long int bottom = 1;
    for (int i = m; i >= 1; i--)
        bottom = (bottom * i) % MOD;

    return top * quick_power(bottom, MOD - 2) % MOD;
}

int main()
{
    int n, k;
    std::cin >> n >> k;

    long long int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        int tmp = n - (i - 1) * k;
        if (tmp < i)
            break;

        ans = (ans + c(tmp, i)) % MOD;
    }

    std::cout << ans;
    return 0;
}