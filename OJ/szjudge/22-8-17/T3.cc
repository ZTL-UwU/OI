#include <iostream>

using u64 = unsigned long long;
using ui128 = __uint128_t;

const u64 MOD = 1e9 + 7;
const int MAX_N = 1e3 + 10;

ui128 fib[MAX_N];

void get_fib()
{
    fib[1] = 1;
    fib[2] = 1;

    for (int i = 3; i < MAX_N; i++)
        fib[i] = fib[i - 1] + fib[i - 2];
}

ui128 gcd(ui128 a, ui128 b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main()
{
    get_fib();

    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        int n, m;
        std::cin >> n >> m;

        u64 ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                ans = (ans + gcd(fib[i], fib[j]) % MOD) % MOD;

        std::cout << ans << "\n";
    }
    return 0;
}