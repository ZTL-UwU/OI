#include <algorithm>
#include <iostream>
#include <cmath>

const int MAX_N = 1e5 + 10;

int x[MAX_N];
int y[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m, z;
    std::cin >> n >> m >> z;

    long long ans = 0;
    for (int i = 0; i < m; i++)
    {
        int q;
        std::cin >> x[i] >> y[i] >> q;

        ans += q;
    }

    std::sort(x, x + m);
    std::sort(y, y + m);

    int mid_x = (m + (m % 2)) / 2 - 1;
    int mid_y = (m + (m % 2)) / 2 - 1;
    for (int i = 0; i < m; i++)
        ans += std::abs(x[mid_x] - x[i]) + std::abs(y[mid_y] - y[i]);

    std::cout << ans << "\n" << x[mid_x] << " " << y[mid_y];

    return 0;
}
