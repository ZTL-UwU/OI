#include <algorithm>
#include <iostream>
#include <cstdio>

const int INF = 0x7fffffff;
const int MAX_N = 1e4 + 10;
const int MAX_R = 1e8;

int tree[MAX_N * 4];
int ans[MAX_R];
int a[MAX_N];

inline void build(int l, int r, int k)
{
    if (l == r)
    {
        tree[k] = a[l];
        return;
    }

    build(l, (r + l) / 2, k * 2);
    build((r + l) / 2 + 1, r, k * 2 + 1);
    tree[k] = std::min(tree[k * 2], tree[k * 2 + 1]);
}

int target_l, target_r;
inline int query(int l, int r, int k)
{
    if (target_l <= l and r <= target_r)
        return tree[k];

    int res1 = INF;
    int res2 = INF;
    if (target_l <= (r + l) / 2)
        res1 = query(l, (r + l) / 2, k * 2);
    if (target_r > (r + l) / 2)
        res2 = query((r + l) / 2 + 1, r, k * 2 + 1);
    return std::min(res1, res2);
}

int main()
{
   std::freopen("busy.in", "r", stdin);
   std::freopen("busy.out", "w", stdout);
    
    int n;
    std::scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        std::scanf("%d", &a[i]);

    int L;
    int R;
    std::scanf("%d %d", &L, &R);

    build(1, n, 1);

    int size = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            target_l = i;
            target_r = j;

            ans[size++] = (j - i + 1) * query(1, n, 1);
        }
    }

    std::sort(ans + 1, ans + size);
    
    for (int i = L; i <= R; i++)
        std::printf("%d ", ans[i]);
    return 0;
}
