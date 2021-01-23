#include <iostream>
#include <set>

const int MAX_N = 2e6;

std::set<int> st[MAX_N];
int color[MAX_N];
int fa[MAX_N];
int ans;

inline void merge(int x, int y)
{
    for (auto i : st[x])
    {
        if (color[i - 1] == y)
            ans--;
        if (color[i + 1] == y)
            ans--;

        st[y].insert(i);
    }
    for (auto i : st[x])
        color[i] = y;

    st[x].clear();
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        std::cin >> color[i];

        st[color[i]].insert(i);
        fa[color[i]] = color[i];
        if (color[i] != color[i - 1])
            ans++;
    }

    for (int i = 0; i < m; i++)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            int x, y;
            std::cin >> x >> y;

            if (x == y)
                continue;
            if (st[fa[x]].size() > st[fa[y]].size())
                std::swap(fa[x], fa[y]);

            merge(fa[x], fa[y]);
        }
        else
            std::cout << ans << "\n";
    }
    return 0;
}