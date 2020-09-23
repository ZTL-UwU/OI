#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

struct query
{
    int id;
    long long l;
    long long r;
};

struct answer
{
    long long a;
    long long b;
};

const int MAXN = 1e5;
long long basket[MAXN];
answer ans[MAXN];
int color[MAXN];
int block[MAXN];
int block_size;
query q[MAXN];

inline bool cmp(query a, query b)
{
    if (block[a.l] == block[b.l])
        return a.r < b.r;
    return block[a.l] < block[b.l];
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    block_size = std::sqrt(n);
    for (int i = 1; i <= n; i++)
        std::cin >> color[i];
    for (int i = 1; i <= n; i++)
        block[i] = (i - 1) / block_size + 1;

    for (int i = 1; i <= m; i++)
    {
        std::cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    std::sort(q + 1, q + m + 1, cmp);

    int l = 0;
    int r = 0;
    long long res = 0;
    for (int i = 1; i <= m; i++)
    {
        if (q[i].l == q[i].r)
        {
            ans[q[i].id].a = 0;
            ans[q[i].id].b = 1;
            continue;
        }

        while (q[i].l < l)
        {
            l--;
            res += basket[color[l]];
            basket[color[l]]++;
        }
        while (q[i].l > l)
        {
            basket[color[l]]--;
            res -= basket[color[l]];
            l++;
        }
        while (q[i].r < r)
        {
            basket[color[r]]--;
            res -= basket[color[r]];
            r--;
        }
        while (q[i].r > r)
        {
            r++;
            res += basket[color[r]];
            basket[color[r]]++;
        }

        ans[q[i].id].a = res - 1;
        ans[q[i].id].b = (q[i].r - q[i].l + 1) * (q[i].r - q[i].l) / 2;

        long long g = std::__gcd(ans[q[i].id].a, ans[q[i].id].b);

        ans[q[i].id].a /= g;
        ans[q[i].id].b /= g;
    }

    for (int i = 1; i <= m; i++)
        std::cout << ans[i].a << "/" << ans[i].b << "\n";
    return 0;
}