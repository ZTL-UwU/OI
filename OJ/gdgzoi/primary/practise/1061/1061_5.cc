#include <iostream>
#include <cstdio>
#include <type_traits>

inline long long int quick_power(long long int a, int n, int p)
{
    long long int ans = 1;

    while (n != 0)
    {
        if (n % 2 == 1)
            ans = (ans * a) % p;

        a = (a * a) % p;
        n >>= 1;
    }

    return ans;
}

inline long long int c(int n, int m, int p)
{
    long long int top = 1;
    for (int i = n; i >= n - m + 1; i--)
        top = (top * i) % p;

    long long int bottom = 1;
    for (int i = m; i >= 1; i--)
        bottom = (bottom * i) % p;

    return (top * quick_power(bottom, p - 2, p)) % p;
}

inline long long int lucas(int n, int m, int p)
{
    if (m == 0)
        return 1;
    return (c(n % p, m % p, p) * lucas(n / p, m / p, p)) % p;
}

int main()
{
    int t;
    std::scanf("%d", &t);

    while (t--)
    {
        int n, m, p;
        std::scanf("%d %d %d", &n, &m, &p);

        std::printf("%lld\n", lucas(n, m, p));
    }
    return 0;
}