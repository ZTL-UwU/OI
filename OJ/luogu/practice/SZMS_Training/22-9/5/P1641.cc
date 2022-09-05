// C(n + m, m) − C(n + m, m − 1)
#include <iostream>

const int MOD = 20100403;
using i64 = long long;

i64 q_pow(i64 a, int b)
{
    i64 res = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }

    return res;
}

i64 c1 = 1;
i64 c2 = 1;
i64 c3 = 1;
i64 c4 = 1;

int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = n + m; i > n; i--)
        c1 = (c1 * i) % MOD;
    for (int i = m; i >= 1; i--)
        c2 = (c2 * i) % MOD;
    for (int i = n + m; i > n + 1; i--)
        c3 = (c3 * i) % MOD;
    for (int i = m - 1; i >= 1; i--)
        c4 = (c4 * i) % MOD;

    i64 res = ((c1 * q_pow(c2, MOD - 2)) % MOD - (c3 * q_pow(c4, MOD - 2)) % MOD + MOD) % MOD;
    std::cout << res;
    return 0;
}