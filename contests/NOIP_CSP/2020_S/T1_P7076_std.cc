#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int maxn = 1e6 + 6;
int n, m, k, c, ans;
unsigned long long a[maxn], sum, ani, mi;
struct rues
{
    int p, q;
} fg[maxn];
bool vis[100000007];
int main()
{
    freopen("zoo3.in", "r", stdin);
    freopen("zoo3.out", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &c, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%llu", &a[i]);
        sum |= a[i];
    }
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &fg[i].p, &fg[i].q);
    for (int i = 1; i <= m; i++)
        if (sum & (1ull << fg[i].p))
            vis[fg[i].q] = 1;
    for (int i = 1; i <= m; i++)
        if (vis[fg[i].q] == 0)
            ani |= (1ull << fg[i].p);
    for (int i = 0; i < k; i++)
        if ((ani & (1ull << i)) == 0)
            ans++; // 2的几次幂
    std::cout << ans << "\n";
    if (ans == 64)
        cout << 18446744073 << 709551616 - n; //特判很重要
    else
    {
        mi = 1;
        for (int i = 1; i <= ans; i++)
            mi *= 2;
        printf("%llu", mi - 1ull * n);
    }
    return 0;
}