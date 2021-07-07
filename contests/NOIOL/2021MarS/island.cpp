#include <algorithm>
#include <cstdio>

const int MAX_N = 1e5 + 10;

int tiredness[MAX_N];
int happyness[MAX_N];

int main()
{
    std::freopen("island.in", "r", stdin);
    std::freopen("island.out", "w", stdout);

    int n, q;
    std::scanf("%d %d", &n, &q);

    for (int i = 0; i < n; i++)
        std::scanf("%d %d", &tiredness[i], &happyness[i]);

    for (int _i = 0; _i < q; _i++)
    {
        int l, r, c, d;
        std::scanf("%d %d %d %d", &l, &r, &c, &d);

        int ans = 0;
        for (int i = l - 1; i < r; i++)
            if ((tiredness[i] ^ c) <= std::min(happyness[i], d))
                ans++;

        std::printf("%d\n", ans);
    }
    return 0;
}