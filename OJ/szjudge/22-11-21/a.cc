#include <iostream>
#include <cstdio>

const int MAX_N = 1e7;
const int P = 1145141999;
using u64 = unsigned long long;

u64 a[MAX_N];
u64 b[MAX_N];

namespace read
{
    u64 seed;
    u64 rnd()
    {
        u64 x = seed;
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        return seed = x;
    }
} // namespace read

int main()
{
    std::freopen("a.in", "r", stdin);
    std::freopen("a.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m, q, w;
    std::cin >> n >> m >> read::seed >> w;
    std::cin >> q;

    for (int i = 0; i <= n; i++)
        a[i] = read::rnd() % w;
    for (int i = 0; i <= m; i++)
        b[i] = read::rnd() % w;

    for (int _i = 0; _i < q; _i++)
    {
        u64 ans = 0;
        int l, r;
        std::cin >> l >> r;

        for (int i = l; i <= r; i++)
            for (int j = 0; j <= n && i - j >= 0; j++)
                if (i - j <= m)
                    ans = (ans + a[j] * b[i - j]) % P;

        std::cout << ans << "\n";
    }
    return 0;
}