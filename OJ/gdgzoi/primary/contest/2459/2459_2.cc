#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

struct edge
{
    int u;
    int v;
    int w;
};

const int INF = 0x7fffffff;
const int MAXN = 1e5;
std::vector<edge> e;
int fa[MAXN];

inline int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

inline void init_union_find()
{
    for (int i = 0; i < MAXN; i++)
        fa[i] = i;
}

inline int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}

inline void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    fa[fx] = fy;
}

inline bool cmp(edge x, edge y) { return x.w > y.w; }

int main()
{
    int n, m;
    std::cin >> n >> m;
    init_union_find();
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        e.push_back((edge){u, v, w});
        merge(u, v);
    }
    int start, end;
    std::cin >> start >> end;

    if (find(start) != find(end))
    {
        std::cout << "IMPOSSIBLE";
        return 0;
    }

    int ans_a = 0;
    int ans_b = 0;
    double ans = INF;
    std::sort(e.begin(), e.end(), cmp);
    for (size_t i = 0; i < e.size(); i++)
    {
        init_union_find();
        for (size_t j = i; j < e.size(); j++)
        {
            merge(e[j].u, e[j].v);
            if (find(start) == find(end))
            {
                double tmp = ((double)e[i].w) / ((double)e[j].w);
                if (tmp < ans)
                {
                    ans_a = e[i].w;
                    ans_b = e[j].w;
                    ans = tmp;
                }

                break;
            }
        }
    }

    int gg = gcd(ans_a, ans_b);
    if (ans_a / ans_b * ans_b == ans_a)
    {
        std::cout << ans_a / ans_b;
        return 0;
    }

    std::cout << ans_a / gg << "/" << ans_b / gg;
    return 0;
}