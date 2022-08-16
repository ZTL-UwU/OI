#include <bits/stdc++.h>
#define int long long
const int mod = 1e9 + 7;
using namespace std;

int n, m, k;
int a, b, ans;
int lie[1000005], hang[1000005];

signed main()
{
    scanf("%lld%lld%lld", &n, &m, &k);

    for (int i = 1; i <= m; ++i)
        lie[i] = 1;
    for (int i = 1; i <= n; ++i)
        hang[i] = 1;

    for (int i = 1; i <= k; ++i)
    {
        char c[5];
        int a, b;
        scanf("%s", c);
        scanf("%lld%lld", &a, &b);
        if (c[0] == 'R')
            hang[a] = hang[a] * b % mod;
        else
            lie[a] = lie[a] * b % mod;
    }

    a = 0;
    b = 0;
    for (int i = 1; i <= m; ++i)
    {
        a = (a + lie[i] * m % mod) % mod;
        // a += lie[i] * m;
        // 修改完列的矩阵 b 每一行的相差数。
        b = (b + lie[i] * i % mod) % mod;
        // b += lie[i] * i;
        // 求修改完列的矩阵 b 的第一行的和。
    }

    for (int i = 1; i <= n; ++i)
    {
        ans = (ans + (b + a * (i - 1) % mod) * hang[i] % mod) % mod;
        // ans += b + a * (i - 1) * hang[i];
        // 求答案，这不用说了吧。
    }

    printf("%lld", ans % mod);
    return 0;
}
