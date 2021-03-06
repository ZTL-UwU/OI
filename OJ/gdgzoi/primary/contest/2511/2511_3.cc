#include <algorithm>
#include <iostream>
#include <cstring>

const int MAX_N = 1e5 + 10;
const int MAX_M = MAX_N;

struct edge
{
    int u;
    int v;
    int w;
};

bool covered[MAX_N];
int origin[MAX_N];
edge e[MAX_M];
int fa[MAX_N];
int n, m;

class union_search
{
public:
    inline union_search(int n)
    {
        for (int i = 0; i <= n; i++)
            fa[i] = i;
    }

    inline int find(int x) { return fa[x] == x ? x : find(fa[x]); }

    inline void merge(int x, int y)
    {
        int fx = find(x);
        int fy = find(y);

        fa[fx] = fy;
    }
};

inline bool check(int key)
{
    std::memset(covered, 0, sizeof(covered));
    union_search uns = union_search(n);

    for (int i = 0; i < m; i++)
        if (e[i].w >= key)
            uns.merge(e[i].u - 1, e[i].v - 1);

    for (int i = 0; i < n; i++)
        if (origin[i] != i and uns.find(i) != uns.find(origin[i]))
            return false;

    return true;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        std::cin >> origin[i];
        origin[i]--;
    }

    bool flag = true;
    for (int i = 0; i < n; i++)
    {
        if (origin[i] != i)
        {
            flag = false;
            break;
        }
    }

    if (flag)
    {
        std::cout << "-1";
        return 0;
    }

    for (int i = 0; i < m; i++)
        std::cin >> e[i].u >> e[i].v >> e[i].w;

    std::sort(e, e + m, [](edge e1, edge e2) -> bool { return e1.w < e2.w; });

    int l = 0;
    int r = m - 1;

    while (r - l > 1)
    {
        int mid = (r + l) / 2;

        if (check(e[mid].w))
            l = mid;
        else
            r = mid;
    }

    std::cout << e[l].w;
    return 0;
}