#include <algorithm>
#include <iostream>

const int MAX_N = 5e5 + 10;
const int MOD = 998244353;

int a[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    std::sort(a, a + n);

    long long ans = 0;
    for (int i = 0; i < n / 2; i++)
        ans = (ans + a[i]) % MOD;
    for (int i = n / 2; i < n; i++)
        ans = (ans * a[i]) % MOD;

    std::cout << ans;
    return 0;
}
