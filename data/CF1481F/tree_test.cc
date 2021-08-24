#include <bits/stdc++.h>
#include <algorithm>

#include "../libxl.hpp"

using namespace std;

inline std::vector<std::pair<int, int>> tree(int n)
{
    assert(n > 0);
    std::vector<std::pair<int, int>> ret;
    if (n == 1)
        return ret;
    std::vector<int> prufer;
    prufer.resize(n - 2);
    for (int &v : prufer)
        v = lxl::mk_rand<int>(1, n);

    int deg[n + 1];
    std::fill(deg + 1, deg + n + 1, 1);
    for (int x : prufer)
        ++deg[x];
    int ptr = 0;
    while (deg[++ptr] != 1)
        ;
    int leaf = ptr;
    for (int x : prufer)
    {
        ret.emplace_back(x, leaf);
        if (--deg[x] == 1 && x < ptr)
            leaf = x;
        else
        {
            while (deg[++ptr] != 1)
                ;
            leaf = ptr;
        }
    }
    ret.emplace_back(leaf, n);
    return ret;
}

int main()
{
    auto tr = tree(5);
    for (auto [x, y] : tr)
        std::cout << x << ' ' << y << std::endl;
}