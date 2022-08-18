#include <iostream>
#include <iomanip>
#include <cmath>

const int MAX_N = 1e3 + 10;

struct node
{
    int v;
    int x;
    bool super;
};

node fa[MAX_N];

int main()
{
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n - 1; i++)
    {
        int u, v, x;
        bool super;
        std::cin >> u >> v >> x >> super;
        fa[v] = {u, x, super};
    }

    double ans = -1;
    for (int i = 1; i <= n; i++)
    {
        double need;
        std::cin >> need;

        if (need != -1)
        {
            int u = i;
            while (u != 1)
            {
                need = (fa[u].super ? std::sqrt(need) : need) / fa[u].x * 100.0;
                u = fa[u].v;
            }

            ans = std::max(ans, need);
        }
    }

    std::cout << std::fixed << std::setprecision(6) << ans;
    return 0;
}