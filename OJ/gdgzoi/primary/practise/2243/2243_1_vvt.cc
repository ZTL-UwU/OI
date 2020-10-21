#include <iostream>
#include <string.h>
#include <vector>
const int MAXN = 2e5 + 10;
namespace vvt
{
    std::vector<int> v;
    void insert(int val)
    {
        v.insert(std::lower_bound(v.begin(), v.end(), val), val);
    }
    void erase(int val)
    {
        v.erase(std::lower_bound(v.begin(), v.end(), val));
    }
    int find(int rank)
    {
        if (rank > v.size())
            return 1;
        return v[v.size() - rank];
    }
} // namespace vvt
namespace uf
{
    int size[MAXN];
    int fa[MAXN];
    void init()
    {
        for (int i = 0; i < MAXN; i++)
        {
            size[i] = 1;
            fa[i] = i;
        }
    }
    int find(int x)
    {
        if (fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }
    void merge(int x, int y)
    {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy)
            return;
        fa[fy] = fx;
        if (size[fx] != 1)
            vvt::erase(size[fx]);
        if (size[fy] != 1)
            vvt::erase(size[fy]);
        size[fx] += size[fy];
        vvt::insert(size[fx]);
    }
} // namespace uf
int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    // vvt::v.reserve(n + 10);
    uf::init();
    while (q--)
    {
        int type;
        std::cin >> type;
        if (type == 0)
        {
            int x, y;
            std::cin >> x >> y;
            uf::merge(x, y);
        }
        else
        {
            int k;
            std::cin >> k;
            std::cout << vvt::find(k) << "\n";
        }
    }
    return 0;
}