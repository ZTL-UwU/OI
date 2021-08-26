#include <iostream>

const int MOD = 12345;

long long quick_pow(long long a, int n)
{
    long long ans = 1;
    while (n != 0)
    {
        if (n % 2 == 1)
            ans = (ans * a) % MOD;
        a = ((a % MOD) * (a % MOD)) % MOD;
        n /= 2;
    }

    return ans;
}

long long c(int n, int m)
{
    if (n == m)
        return 1;
    if (n < m)
        return 0;

    long long top = 1;
    long long bottom = 1;

    for (int i = n; i >= n - m + 1; i--)
        top *= i;
    for (int i = m; i >= 1; i--)
        bottom *= i;

    return top * quick_pow(bottom, MOD - 2) % MOD;
}

int main()
{
    int n;
    std::cin >> n;

    long long ans = 0;
    for (int i = 1; i <= n; i += 2)
    {
        ans = (ans + (c(n, i) - c(n - 1, i)) * quick_pow(9, n - i) % MOD) % MOD;
        if (i != n)
            ans = (ans + (c(n - 1, i) * 8 % MOD) * quick_pow(9, n - i - 1) % MOD) % MOD;
    }

    std::cout << (MOD + 9 * quick_pow(10, n - 1) % MOD - ans) % MOD;
    return 0;
}
