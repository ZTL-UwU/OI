#include <iostream>

const int MAX_N = 1e6 + 10;

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

    long long ans = 0;

    for (int i = 0; i < n; i++)
    {
        long long sum = a[i];
        for (int j = i + 1; j < n; j++)
        {
            sum |= a[j];
            if (sum < m)
                ans++;
            else
                break;
        }
    }

    std::cout << ans;
    return 0;
}