#include "../libxl.hpp"
#include <iostream>
#include <vector>

const std::string SAMPLE = "9 3\n"
                           "1 2 2 4 4 4 3 1";

std::vector<std::pair<int, int>> tree(int n)
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

const int MAX_N = 1e5 + 10;
std::vector<int> t1[MAX_N];
int fa[MAX_N];

void dfs(int u)
{
    for (auto v : t1[u])
    {
        if (v != fa[u])
        {
            fa[v] = u;
            dfs(v);
        }
    }
}

void mk_tree(int n)
{
    const auto t = tree(n);
    for (auto p : t)
    {
        t1[p.first].push_back(p.second);
        t1[p.second].push_back(p.first);
    }

    dfs(1);
}

int main()
{
    int type;
    std::cin >> type;

    if (type == 0)
    {
        std::cout << SAMPLE;
        return 0;
    }

    int n = 0;
    std::vector<int> tree_res;

    if (1 <= type && type <= 5)
    {
        if (type == 1)
            n = lxl::mk_rand<int>(1e1, 1e2);
        else if (type == 2)
            n = lxl::mk_rand<int>(1e2, 1e3);
        else if (type == 3)
            n = lxl::mk_rand<int>(1e3, 1e4);
        else if (type == 4)
            n = lxl::mk_rand<int>(1e4, 1e5);
        else if (type == 5)
            n = 1e5;

        mk_tree(n);
    }
    else if (type == 6)
    {
        n = 1e5;
        for (int i = 3; i <= n; i++)
            fa[i] = lxl::mk_rand<int>(1, 2);
    }
    else if (type == 7)
    {
        n = 1e5;
        for (int i = 2; i <= n; i++)
            fa[i] = i - (lxl::mk_bool(0.9) ? 1 : 2);
    }

    std::cout << n << " " << lxl::mk_rand(0, n) << "\n";
    for (int i = 2; i <= n; i++)
        std::cout << fa[i] << " ";
    return 0;
}