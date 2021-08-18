#include <iostream>

const int MAX_N = 1e6 + 10;
const int MOD = 1e9 + 7;

long long v[MAX_N];
long long h[MAX_N];

int main()
{
    int n, m, k;
    std::cin >> n >> m >> k;

    std::fill(v, v + m + 10, 1);
    std::fill(h, h + n + 10, 1);

    for (int _i = 0; _i < k; _i++)
    {
        char op;
        int x, y;
        std::cin >> op >> x >> y;

        if (op == 'R')
            h[x] = (h[x] * y) % MOD;
        else if (op == 'S')
            v[x] = (v[x] * y) % MOD;
    }

    long long line1 = 0;
    long long diff = 0;
    for (int i = 1; i <= m; i++)
    {
        line1 = (line1 + v[i] * i % MOD) % MOD;
        diff = (diff + v[i] * m % MOD) % MOD;
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (ans + (line1 + diff * (i - 1) % MOD) * h[i] % MOD) % MOD;
    std::cout << ans % MOD;

    return 0;
}