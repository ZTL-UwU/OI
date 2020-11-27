#include <iostream>

const int MAX_N = 6e5;

int fa[MAX_N];
int n;

inline void init()
{
    for (int i = 0; i < MAX_N; i++)
        fa[i] = i;
}

inline int find(int x)
{
    if (fa[x] == x)
        return x;
    fa[x] = find(fa[x]);
    return fa[x];
}

inline void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);

    if (fx != fy)
        fa[fx] = fy;
}

inline bool solve(int opt, int x, int y)
{
    if (x > n or y > n)
        return false;

    if (opt == 1)
    {
        if (find(x + n) == find(y) or find(x + n * 2) == find(y))
            return false;

        merge(x, y);
        merge(x + n, y + n);
        merge(x + n * 2, y + n * 2);
    }

    if (opt == 2)
    {
        if (find(x) == find(y) or find(x + n * 2) == find(y))
            return false;

        merge(x, y + n * 2);
        merge(x + n * 2, y + n);
        merge(x + n, y);
    }

    return true;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int q;
    std::cin >> n >> q;

    init();

    int ans = 0;
    for (int t = 0; t < q; t++)
    {
        int opt, x, y;
        std::cin >> opt >> x >> y;

        if (not solve(opt, x, y))
            ans++;
    }

    std::cout << ans;
    return 0;
}