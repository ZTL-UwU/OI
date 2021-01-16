#include <algorithm>
#include <iostream>

const int MAX_N_M = 1e5 + 10;

long long int a[MAX_N_M];
long long int b[MAX_N_M];

long long int ans;

int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    for (int i = 0; i < m; i++)
        std::cin >> b[i];

    std::sort(a, a + n);
    std::sort(b, b + n);

    for (int i = 0; i < n; i++)
        ans += a[i] * b[i];

    std::cout << ans;
    return 0;
}