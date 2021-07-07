#include <iostream>

const int INF = 0x7fffffff;
const int MAX_N = 1e5 + 10;

int a[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    for (int _i = 0; _i < m; _i++)
    {
        int x, y;
        std::cin >> x >> y;

        int ans = INF;
        for (int i = 0; i < n; i++)
            if (a[i] == x)
                a[i] = y;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (a[i] == a[j])
                {
                    ans = std::min(ans, j - i);
                    break;
                }
            }
        }

        std::cout << ans << "\n";
        if (ans == 1)
        {
            for (int i = _i + 1; i < m; i++)
                std::cout << "1\n";
            return 0;
        }
    }
    return 0;
}