#include <iostream>

using i64 = long long;

const int MAX_Q = 5e4 + 10;
const int MAX_N = 2e5 + 10;
const int MOD = 1e9 + 7;

i64 f[MAX_N];
int n[MAX_Q];

i64 qpow(i64 a, i64 b)
{
    i64 res = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
            res = (res * a) % MOD;

        a = (a * a) % MOD;
        b /= 2;
    }

    return res % MOD;
}

int main()
{
    int t;
    std::cin >> t;

    int max = 0;
    for (int i = 0; i < t; i++)
    {
        std::cin >> n[i];
        max = std::max(max, n[i]);
    }

    f[0] = 1;
    for (int i = 0; i <= max + 1; i++)
        f[i + 1] = (f[i] * (4 * i + 2) % MOD) * qpow(i + 2, MOD - 2) % MOD;

    for (int i = 0; i < t; i++)
        std::cout << f[n[i]] % MOD << "\n";
    return 0;
}