#include <bits/stdc++.h>
#define lld long long
using namespace std;
const lld mod = 1e9 + 7;
lld qpow(lld a, lld b, lld p)
{
    lld ret = 1;
    for (; b; b >>= 1, a = a * a % p)
        if (b & 1)
            ret = ret * a % p;
    return ret;
}
lld _inv(lld x) { return qpow(x, mod - 2, mod); }
lld inv[10001];
char nums[] = "012359";
lld C(lld n, lld m)
{
    lld fac = 1;
    for (int i = n - m + 1; i <= n; ++i)
        fac = fac * i % mod;
    for (int i = 1; i <= m; ++i)
        fac = fac * inv[i] % mod;
    return fac;
}
char buf[101];
void solve(lld x)
{
    int top = 0;
    for (; x; x = (x - 1) / 5)
        buf[++top] = nums[(x - 1) % 5 + 1];
    for (int i = top; i >= 1; --i)
        putchar(buf[i]);
}
int main()
{
    for (int i = 1; i <= 10000; ++i)
        inv[i] = qpow(i, mod - 2, mod);
    int T, n, m;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        std::cout << "-" << C(n, m) << "\n";
        solve(C(n, m));
        puts("");
    }
}