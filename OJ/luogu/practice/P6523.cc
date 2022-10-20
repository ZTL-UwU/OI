#include <iostream>

const int MAX_N = 1e5 + 10;
using i64 = long long;

i64 ans[MAX_N];
i64 a[MAX_N];

i64 gcd(i64 x, i64 y)
{
    if (y == 0)
        return x;
    return gcd(y, x % y);
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
        int n, m;
        std::cin >> n >> m;

        int diff = 0;
        for (int i = 0; i < n - 1; i++)
        {
            std::cin >> a[i];
            if (i != 0 && a[i] != a[i - 1])
                diff = i - 1;
        }

        ans[diff + 1] = gcd(a[diff], a[diff + 1]);
        bool has_ans = true;
        for (int i = diff; i >= 0; i--)
        {
            ans[i] = a[i] / ans[i + 1];
            if (ans[i] > m)
            {
                has_ans = false;
                break;
            }
        }

        for (int i = diff + 1; i < n; i++)
        {
            ans[i + 1] = a[i] / ans[i];
            if (ans[i] > m)
            {
                has_ans = false;
                break;
            }
        }

        if (!has_ans)
            std::cout << "-1";
        else
            for (int i = 0; i < n; i++)
                std::cout << ans[i] << " ";
        std::cout << "\n";
    }
    return 0;
}