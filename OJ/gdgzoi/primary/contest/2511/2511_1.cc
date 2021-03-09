#include <algorithm>
#include <iostream>

const int MAX_N = 1e3 + 10;

int b[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, k;
    std::cin >> n >> k;

    int max_b = -1;
    for (int i = 0; i < n; i++)
    {
        std::cin >> b[i];
        max_b = std::max(max_b, b[i]);
    }

    int ans = 0;
    for (int m = 1; m <= max_b; m++)
    {
        int l = 0;
        for (int j = 0; j < n; j++)
            l += b[j] / m;

        if (l < k / 2)
            break;
        else if (l >= k)
            ans = std::max(ans, m * k / 2);
        else
        {
            std::sort(b, b + n, [m](int a, int b) -> bool { return a % m > b % m; });

            int tmp = m * (l - k / 2);
            for (int j = 0; j < std::min(k - l, n); j++)
                tmp += b[j] % m;

            ans = std::max(ans, tmp);
        }
    }

    std::cout << ans;
    return 0;
}