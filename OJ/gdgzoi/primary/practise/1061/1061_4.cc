#include <iostream>
#include <cstdio>

const int MAX_N = 1e6 + 10;
const int MOD = 1e9 + 7;

long long int factorial[MAX_N];
long long int d[MAX_N];

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
    return ((factorial[n] * quick_power(factorial[m], MOD - 2) % MOD) * quick_power(factorial[n - m], MOD - 2)) % MOD;
}

inline long long int lucas(int n, int m)
{
    if (m == 0)
        return 1;
    return (c(n % MOD, m % MOD) * lucas(n / MOD, m / MOD)) % MOD;
}

inline void get_factorial(int max_num)
{
    factorial[0] = 1;
    for (int i = 1; i <= max_num; i++)
        factorial[i] = (factorial[i - 1] * i) % MOD;
}

inline void get_d(int max_num)
{
    d[1] = 0;
    d[2] = 1;
    d[3] = 2;

    for (int i = 4; i <= max_num; i++)
        d[i] = (i - 1) * (d[i - 1] + d[i - 2]) % MOD;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    get_factorial(MAX_N - 1);
    get_d(MAX_N - 1);

    while (t--)
    {
        int n, m;
        std::cin >> n >> m;

        if (n - m == 1)
            std::cout << "0\n";
        else if (n == m)
            std::cout << "1\n";
        else
            std::cout << (lucas(n, m) * d[n - m]) % MOD << "\n";
    }
    return 0;
}