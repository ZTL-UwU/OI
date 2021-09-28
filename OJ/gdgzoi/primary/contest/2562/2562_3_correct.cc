#include <algorithm>
#include <iostream>
#include <climits>

using u64 = unsigned long long;

const int base = 233;
const int MAX_N = 2e5 + 10;
const u64 MOD = ULLONG_MAX / MAX_N;

u64 num[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::string str;
    std::cin >> n >> m >> str;

    u64 high_bit = 1;

    for (int _i = 0; _i < m - 1; _i++)
        high_bit = high_bit * base % MOD;
    for (int i = 0; i < m; i++)
        num[0] = (num[0] * base % MOD + str[i]) % MOD;
    for (int i = m; i < n; i++)
        num[i - m + 1] = (((num[i - m] - high_bit * str[i - m] % MOD + MOD) % MOD) * base % MOD + str[i]) % MOD;
    std::sort(num, num + n - m + 1);

    int ans = 1;
    for (int i = 1; i <= n - m; i++)
        if (num[i] != num[i - 1])
            ans++;
    std::cout << ans;
    return 0;
}