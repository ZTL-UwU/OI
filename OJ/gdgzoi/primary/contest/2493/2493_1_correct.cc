#include <algorithm>
#include <iostream>

const int MAX_N_M = 1e5 + 10;

int a[MAX_N_M];
int b[MAX_N_M];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    for (int i = 0; i < m; i++)
        std::cin >> b[i];
    
    std::sort(a, a + n);
    std::sort(b, b + m);

    long long int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > 0)
            break;
        ans += 1LL * a[i] * b[i];
    }

    int p = m - 1;
    for (int i = n - 1; i >= 0; i--)
    {
        if (a[i] <= 0)
            break;
        ans += 1LL * a[i] * b[p--];
    }

    std::cout << ans;
    return 0;
}