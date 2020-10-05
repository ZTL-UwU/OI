#include <bits/stdc++.h>

#include <fmt/core.h>

int main()
{
    srand(time(0));
    freopen("./2464_0_large.in", "w", stdout);

    int w, n, m;
    std::cin >> w >> n >> m;

    fmt::print("{}\n", w);
    for (int i = 0; i < w; i++)
    {
        fmt::print("{} {}\n", n, m);
        for (int i = 0; i < m; i++)
        {
            int s = rand() % m + 1;
            int t = rand() % m + 1;
            fmt::print("{} {} {}\n", std::min(s, t), std::max(s, t), rand() % (int)1e8);
        }
    }
    return 0;
}