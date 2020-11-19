#include <iostream>
#include <cstdio>
#include <type_traits>

const int MOD = 1e4 + 7;

inline long long int quick_power(long long int a, int n)
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

    return (top * quick_power(bottom, MOD - 2)) % MOD;
}

inline long long int lucas(int n, int m)
{
    if (m == 0)
        return 1;
    return (c(n % MOD, m % MOD) * lucas(n / MOD, m / MOD)) % MOD;
}

int main()
{
    int t;
    std::scanf("%d", &t);

    while (t--)
    {
        int n, m;
        std::scanf("%d %d", &n, &m);

        std::printf("%lld\n", lucas(n, m));
    }
    return 0;
}