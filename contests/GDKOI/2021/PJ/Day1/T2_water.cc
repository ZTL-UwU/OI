#include <iostream>

const int MAX_N = 2e5 + 10;

int height[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, q;
    std::cin >> n >> q;

    for (int i = 1; i <= n; i++)
        std::cin >> height[i];

    for (int _q = 0; _q < q; _q++)
    {
        int x, y;
        std::cin >> x >> y;

        long long int res = y - height[x];
        for (int i = x - 1; i >= 1 and height[i] < y; i--)
            res += y - height[i];
        for (int i = x + 1; i <= n and height[i] < y; i++)
            res += y - height[i];

        std::cout << res << "\n";
    }
    return 0;
}