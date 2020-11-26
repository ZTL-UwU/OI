#include <iostream>
#include <cmath>

const int MAX_N = 5e4;

int size[MAX_N];
int dis[MAX_N];
int fa[MAX_N];

inline void init()
{
    for (int i = 0; i < MAX_N; i++)
    {
        fa[i] = i;
        size[i] = 1;
    }
}

inline int find(int x)
{
    if (fa[x] == x)
        return x;

    int root = find(fa[x]);
    dis[x] += dis[fa[x]];
    return fa[x] = root;
}

inline void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);

    if (fx != fy)
    {
        fa[fx] = fy;
        dis[fx] += size[fy];
        size[fy] += size[fx];
    }
}

inline int check(int x, int y)
{
    int fx = find(x);
    int fy = find(y);

    if (fx != fy)
        return -1;
    return std::abs(dis[x] - dis[y]) - 1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int T;
    std::cin >> T;

    init();
    for (int i = 0; i < T; i++)
    {
        char opt;
        int x, y;
        std::cin >> opt >> x >> y;

        if (opt == 'M')
            merge(x, y);
        else
            std::cout << check(x, y) << "\n";
    }
    return 0;
}