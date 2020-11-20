#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cstdio>

const int MOD = 1e5 + 3;
const int MAX_N = 1e4;

long long int factorial[MAX_N];

/**
 *    a
 * +-------+
 * |       |
 * |       | b
 * |       |
 * |       +-------+
 * |           c   |
 * |               | d
 * |               |
 * +---------------+
 *
 */

inline void get_factorial(int max_num)
{
    factorial[0] = 1;
    for (int i = 1; i <= max_num; i++)
        factorial[i] = (factorial[i - 1] * i) % MOD;
}

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

inline long long int combination(int n, int m)
{
    return ((factorial[n] * quick_power(factorial[m], MOD - 2) % MOD) * quick_power(factorial[n - m], MOD - 2)) % MOD;
}

inline long long int lucas(int n, int m)
{
    if (m == 0)
        return 1;
    return (combination(n % MOD, m % MOD) * lucas(m / MOD, m / MOD)) % MOD;
}

inline long long int solve(int n, int m, int k)
{
    if (k > n or k > m)
        return 0;
    return ((lucas(n, k) * lucas(m, k) % MOD) * factorial[k]) % MOD;
}

int main()
{
    int a, b, c, d, k;
    std::cin >> a >> b >> c >> d >> k;

    get_factorial(MAX_N - 10);

    unsigned long long int ans = 0;
    for (int i = 0; i <= k; i++)
        ans = (ans + (solve(a, b, i) * solve(a + c - i, d, k - i)) % MOD) % MOD;

    std::cout << ans % MOD;
    return 0;
}