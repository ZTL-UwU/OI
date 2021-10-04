//????????????????????????????????????????
//????????????????????????????????????????
//????????????????????????????????????????

#include <algorithm>
#include <iostream>
#include <vector>

const int MAX_N = 1e4 + 10;

struct edge
{
    int u, v;
    int l, r;
};

std::vector<edge> E;
int n, m;

namespace ufind
{
    int fa[MAX_N];

    void init()
    {
        for (int i = 0; i <= n; i++)
            fa[i] = i;
    }

    int find(int x)
    {
        if (fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }

    bool same_fa(int x, int y) { return find(x) == find(y); }

    void merge(int x, int y)
    {
        if (!same_fa(x, y))
            fa[find(x)] = find(y);
    }
} // namespace ufind

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m;

    for (int _i = 0; _i < m; _i++)
    {
        int u, v, l, r;
        std::cin >> u >> v >> l >> r;

        E.emplace_back(edge{u, v, l, r});
    }

    std::sort(E.begin(), E.end(), [](edge e1, edge e2) -> bool { return e1.r > e2.r; });

    edge ans{0, 0, 0, 0};
    for (auto e_l : E)
    {
        ufind::init();
        edge lim{0, 0, e_l.l, e_l.r};

        for (auto e_r : E)
        {
            if (e_r.l <= lim.l)
            {
                ufind::merge(e_r.u, e_r.v);
                lim.r = std::min(lim.r, e_r.r);

                if (ufind::same_fa(1, n))
                {
                    if (lim.r - lim.l > ans.r - ans.l)
                        ans = lim;
                    break;
                }
            }
        }
    }

    if (ans.r == 0 && ans.l == 0)
        std::cout << 0;
    else
    {
        std::cout << ans.r - ans.l + 1 << "\n";
        for (int i = ans.l; i <= ans.r; i++)
            std::cout << i << " ";
    }

    return 0;
}