// WILEIVUQI

#include <iostream>
#include <vector>

const int MAX_N = 1e5 + 10;

std::vector<int> g[MAX_N];
bool installed[MAX_N];
bool have_son[MAX_N];
int fa[MAX_N];

int install(int pkg)
{
    if (installed[pkg])
        return 0;

    have_son[pkg] = true;
    installed[pkg] = true;
    return install(fa[pkg]) + 1;
}

int uninstall(int pkg)
{
    if (!installed[pkg])
        return 0;

    int res = 0;
    have_son[pkg] = false;
    if (installed[pkg])
    {
        installed[pkg] = false;
        res = 1;
    }
    for (auto v : g[pkg])
        if (have_son[v])
            res += uninstall(v);

    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    for (int i = 1; i < n; i++)
    {
        std::cin >> fa[i];
        g[fa[i]].push_back(i);
    }

    int q;
    std::cin >> q;
    for (int _i = 0; _i < q; _i++)
    {
        std::string op;
        int pkg;
        std::cin >> op >> pkg;

        if (op == "install")
            std::cout << install(pkg) << "\n";
        else
            std::cout << uninstall(pkg) << "\n";
    }
    return 0;
}
