#include <algorithm>
#include <iostream>
#include <cstdio>

const int INF = 0x7fffffff;
const int MAXN = 1e6;
int minn = INF;
int dis[MAXN];
int fa[MAXN];

inline int find(int x)
{
    if (fa[x] == x)
        return x;

    int last = fa[x];
    fa[x] = find(fa[x]);
    dis[x] += dis[last];
    return fa[x];
}

inline void check(int x, int y)
{
    int fa_x = find(x);
    int fa_y = find(y);

    if (fa_x != fa_y)
    {
        fa[fa_x] = fa_y;
        dis[x] = dis[y] + 1;
    }
    else
        minn = std::min(minn, dis[x] + dis[y] + 1);
}

int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i <= n; i++)
        fa[i] = i;

    for (int i = 1; i <= n; i++)
    {
        int to;
        std::cin >> to;
        check(i, to);
    }

    std::cout << minn;
    return 0;
}