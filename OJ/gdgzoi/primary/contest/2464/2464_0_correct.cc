#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXN = 1e4;
int value[MAXN];
int fa[MAXN];

inline int find(int x)
{
    if (fa[x] == x)
        return x;

    int fx = fa[x];
    fa[x] = find(fa[x]);
    value[x] += value[fx];

    return fa[x];
}

inline bool check(int s, int t, int val)
{
    int fs = find(s);
    int ft = find(t);

    if (fs == ft)
        return value[t] - value[s] == val;

    fa[ft] = fs;
    value[ft] = val - value[t] + value[s];
    return true;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int T;
    std::cin >> T;
    while (T--)
    {
        std::memset(value, 0, sizeof(value));

        int n, m;
        std::cin >> n >> m;

        bool flag = true;
        for (int i = 0; i <= n; i++)
            fa[i] = i;
        for (int i = 0; i < m; i++)
        {
            int s, t, val;
            std::cin >> s >> t >> val;
            if (!check(s - 1, t, val))
                flag = false;
        }

        std::cout << std::boolalpha << flag << "\n";
    }
    return 0;
}