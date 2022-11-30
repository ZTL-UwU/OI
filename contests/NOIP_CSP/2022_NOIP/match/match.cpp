#include <iostream>
#include <cstdio>

const int MAX_N = 1e5 + 10;
const int MAX_LOG = 20;
using u64 = unsigned long long;

int sta[MAX_N][MAX_LOG];
int stb[MAX_N][MAX_LOG];
int a[MAX_N];
int b[MAX_N];
int log[MAX_N];

u64 get_max_a(int l, int r)
{
    return std::max(sta[l][log[r - l + 1]], sta[r - (1 << log[r - l + 1]) + 1][log[r - l + 1]]);
}

u64 get_max_b(int l, int r)
{
    return std::max(stb[l][log[r - l + 1]], stb[r - (1 << log[r - l + 1]) + 1][log[r - l + 1]]);
}

int main()
{
    std::freopen("match.in", "r", stdin);
    std::freopen("match.out", "w", stdout);

    int T, n;
    std::cin >> T >> n;

    log[0] = -1;
    for (int i = 1; i < MAX_N; i++)
        log[i] = log[i / 2] + 1;

    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
        sta[i][0] = a[i];
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> b[i];
        stb[i][0] = b[i];
    }

    for (int i = 1; i < MAX_LOG; i++)
    {
        for (int j = 0; j < n - (1 << i) + 1; j++)
        {
            sta[j][i] = std::max(sta[j][i - 1], sta[j + (1 << (i - 1))][i - 1]);
            stb[j][i] = std::max(stb[j][i - 1], stb[j + (1 << (i - 1))][i - 1]);
        }
    }

    int q;
    std::cin >> q;
    for (int _i = 0; _i < q; _i++)
    {
        int l, r;
        std::cin >> l >> r;
        u64 ans = 0;
        for (int p = l; p <= r; p++)
        {
            for (int q = p; q <= r; q++)
            {
                ans += get_max_a(p - 1, q - 1) * get_max_b(p - 1, q - 1);
            }
        }

        std::cout << ans << "\n";
    }
    return 0;
}
