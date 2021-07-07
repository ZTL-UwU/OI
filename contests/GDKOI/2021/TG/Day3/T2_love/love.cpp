#include <iostream>
#include <cstdio>

const int MAX_N = 1e5 + 10;

int sum_a[MAX_N];
long long int sum_b[MAX_N];
long long int ans[MAX_N];

int main()
{
    std::freopen("love.in", "r", stdin);
    std::freopen("love.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    int tmp;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> tmp;
        sum_a[i] = sum_a[i - 1] + tmp;
    }
    for (int i = 1; i <= n; i++)
    {
        std::cin >> tmp;
        sum_b[i] = sum_b[i - 1] + tmp;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (sum_b[j] - sum_b[i - 1] > 0 and sum_a[j] - sum_a[i - 1] <= n and sum_a[j] - sum_a[i - 1] >= -n)
                ans[n + sum_a[j] - sum_a[i - 1]]++;
            if (sum_b[j] - sum_b[i - 1] < 0 and -(sum_a[j] - sum_a[i - 1]) <= n and -(sum_a[j] - sum_a[i - 1]) >= -n)
                ans[n - (sum_a[j] - sum_a[i - 1])]++;
        }
    }

    for (int i = 0; i <= 2 * n; i++)
        std::cout << ans[i] << " ";
    return 0;
}
