#include <iostream>
const int MAXN = 1e6 + 10;
int a[MAXN];
int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];

    long long ans = 0;
    for (int i = 1; i < n; i++)
        ans += std::max(a[i], a[i - 1]);

    std::cout << ans;
    return 0;
}