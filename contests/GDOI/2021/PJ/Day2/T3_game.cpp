#include <iostream>
#include <vector>
#include <cstdio>

const int MAX_N = 1e5 + 10;
int a[MAX_N][2];

std::vector<int> ans;

int main()
{
    std::freopen("game.in", "r", stdin);
    std::freopen("game.out", "w", stdout);

    int n, m;
    std::scanf("%d %d", &n, &m);
    const int mdiv2 = m / 2;

    for (int i = 0; i < n; i++)
        std::scanf("%d", &a[i][0]);

    int k = 0;
    while (true)
    {
        bool win = false;
        for (int i = 0; i < n; i++)
        {
            if (a[i][k] != -1)
            {
                int next = (i + 1) % n;
                while (a[next][k] == -1)
                    next = (next + 1) % n;
                if (next == i)
                {
                    std::printf("%d\n%d", 1, i);
                    return 0;
                }

                const int x_to_y = (a[i][k] - a[next][k] + m) % m;
                const int y_to_x = (a[next][k] - a[i][k] + m) % m;

                const bool x_to_y_b = 0 < x_to_y && x_to_y <= mdiv2;
                const bool y_to_x_b = 0 < y_to_x && y_to_x <= mdiv2;

                if (x_to_y_b && (!y_to_x_b))
                {
                    a[next][k + 1] = -1;
                    win = true;
                }
                if (y_to_x_b && (!x_to_y_b))
                {
                    a[i][k + 1] = -1;
                    win = true;
                }
            }
        }

        if (!win)
            break;

        if (k == 0)
            k = 1;
        else
            k = 0;
    }

    for (int i = 0; i < n; i++)
        if (a[i][k] != -1)
            ans.push_back(i);

    std::printf("%d\n", ans.size());
    for (std::size_t i = 0; i < ans.size(); i++)
        std::printf("%d ", ans[i] + 1);
    return 0;
}