#include <iostream>
#include <cstdio>

int factorial[100000];

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
    return ((factorial[n] * quick_power(factorial[m], p - 2, p) % p) * quick_power(factorial[n - m], p - 2, p)) % p;
}

inline long long int lucas(int n, int m, int p)
{
    if (m == 0)
        return 1;
    return (c(n % p, m % p, p) * lucas(n / p, m / p, p)) % p;
}

inline void get_factorial(int max_num, int p)
{
    factorial[0] = 1;
    for (int i = 1; i <= max_num; i++)
        factorial[i] = (factorial[i - 1] * i) % p;
}

int main()
{
    int t;
    std::scanf("%d", &t);

    while (t--)
    {
        int n, m, p;
        std::scanf("%d %d %d", &n, &m, &p);

        get_factorial(1000, p);
        std::printf("%lld\n", lucas(n, m, p));
    }
    return 0;
}