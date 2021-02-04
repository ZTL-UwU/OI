#include <algorithm>
#include <iostream>
#include <vector>

const int MAX_N = 4e5 + 10;

struct edge
{
    int u, v, w;
    operator int() const;
};
edge::operator int() const { return this->w; }

struct query
{
    int id, start;
};

namespace ufind
{
    int fa[MAX_N];
    int w[MAX_N];

    inline void init()
    {
        for (int i = 0; i < MAX_N; i++)
        {
            fa[i] = i;
            w[i] = 1;
        }
    }

    inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

    inline void merge(int x, int y)
    {
        const int fa_x = find(x);
        const int fa_y = find(y);

        fa[fa_x] = fa_y;
        w[fa_y] += w[fa_x];
    }
} // namespace ufind

std::vector<query> q_v[MAX_N];
std::vector<edge> e_v;
int ans[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    for (int _m = 0; _m < m; _m++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        e_v.push_back((edge){u, v, w});
    }
    std::sort(e_v.begin(), e_v.end());

    int q_num;
    std::cin >> q_num;

    for (int i = 0; i < q_num; i++)
    {
        int start, w;
        std::cin >> start >> w;

        q_v[std::upper_bound(e_v.begin(), e_v.end(), w) - e_v.begin()].push_back((query){i, start});
    }

    for (auto i : q_v[0])
        ans[i.id] = 1;

    ufind::init();

    for (std::size_t i = 0; i < e_v.size(); i++)
    {
        const auto e = e_v[i];
        if (ufind::find(e.u) != ufind::find(e.v))
            ufind::merge(e.u, e.v);

        for (auto v : q_v[i + 1])
            ans[v.id] = ufind::w[ufind::find(v.start)];
    }

    for (int i = 0; i < q_num; i++)
        std::cout << ans[i] << "\n";
    return 0;
}