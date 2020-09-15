#include <map>
#include <set>
#include <cmath>
#include <stack>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define mod 998244353
#define pi acos(-1)
#define inf 0x7fffffff
#define ll long long
using namespace std;
ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
int n, blo;
int v[50005], bl[50005], atag[50005];
vector<int> ve[505];
void reset(int x)
{
    ve[x].clear();
    for (int i = (x - 1) * blo + 1; i <= min(x * blo, n); i++)
        ve[x].push_back(v[i]);
    sort(ve[x].begin(), ve[x].end());
}
void add(int a, int b, int c)
{
    for (int i = a; i <= min(bl[a] * blo, b); i++)
        v[i] += c;
    reset(bl[a]);
    if (bl[a] != bl[b])
    {
        for (int i = (bl[b] - 1) * blo + 1; i <= b; i++)
            v[i] += c;
        reset(bl[b]);
    }
    for (int i = bl[a] + 1; i <= bl[b] - 1; i++)
        atag[i] += c;
}
int query(int a, int b, int c)
{
    int ans = 0;
    for (int i = a; i <= min(bl[a] * blo, b); i++)
        if (v[i] + atag[bl[a]] < c)
            ans++;
    if (bl[a] != bl[b])
        for (int i = (bl[b] - 1) * blo + 1; i <= b; i++)
            if (v[i] + atag[bl[b]] < c)
                ans++;
    for (int i = bl[a] + 1; i <= bl[b] - 1; i++)
    {
        int x = c - atag[i];
        ans += lower_bound(ve[i].begin(), ve[i].end(), x) - ve[i].begin();
    }
    return ans;
}
int main()
{
    n = read();
    blo = sqrt(n);
    for (int i = 1; i <= n; i++)
        v[i] = read();
    for (int i = 1; i <= n; i++)
    {
        bl[i] = (i - 1) / blo + 1;
        ve[bl[i]].push_back(v[i]);
    }
    for (int i = 1; i <= bl[n]; i++)
        sort(ve[i].begin(), ve[i].end());
    for (int i = 1; i <= n; i++)
    {
        int f = read(), a = read(), b = read(), c = read();
        if (f == 0)
            add(a, b, c);
        if (f == 1)
            printf("%d\n", query(a, b, c * c));
    }
    return 0;
}