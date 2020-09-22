#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

struct query
{
    int l;
    int r;
    int id;
};

const int MAXN = 1e6 + 10;
int basket[MAXN];
int value[MAXN];
int block[MAXN];
int block_size;
int ans[MAXN];
query q[MAXN];

inline bool cmp(query a, query b)
{
    if (block[a.l] == block[b.l])
        return a.r < b.r;
    return block[a.l] < block[b.l];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    block_size = std::sqrt(n);
    for (int i = 1; i <= n; i++)
        std::cin >> value[i];
    for (int i = 1; i <= n; i++)
        block[i] = (i - 1) / block_size + 1;

    int m;
    std::cin >> m;
    for (int i = 1; i <= m; i++)
    {
        std::cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    std::sort(q + 1, q + m + 1, cmp);

    int l = 0;
    int r = 0;
    int res = 0;
    for (int i = 1; i <= m; i++)
    {
        while (q[i].l < l)
        {
            l--;
            if (basket[value[l]] == 0)
                res++;
            basket[value[l]]++;
        }
        while (q[i].l > l)
        {
            basket[value[l]]--;
            if (basket[value[l]] == 0)
                res--;
            l++;
        }
        while (q[i].r < r)
        {
            basket[value[r]]--;
            if (basket[value[r]] == 0)
                res--;
            r--;
        }
        while (q[i].r > r)
        {
            r++;
            if (basket[value[r]] == 0)
                res++;
            basket[value[r]]++;
        }

        ans[q[i].id] = res;
    }

    for (int i = 1; i <= m; i++)
        std::cout << ans[i] << "\n";
    return 0;
}