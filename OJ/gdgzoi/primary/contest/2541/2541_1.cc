// WILEIVUQI

#include <algorithm>
#include <iostream>

const int MAX_N = 1e5 + 10;

int a[MAX_N];
int n, k;

bool check()
{
    for (int i = 1; i < n; i++)
        if (a[i] < a[i - 1])
            return true;
    return false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        std::cin >> n >> k;
        for (int i = 0; i < n; i++)
            std::cin >> a[i];

        int ans = 0;
        while (check())
        {
            for (int i = 0; i <= n - k; i++)
                std::sort(a + i, a + i + k);
            ans++;
        }

        std::cout << ans << '\n';
    }
    return 0;
}