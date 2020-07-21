#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define tt 1000000007
#define maxn 55
using namespace std;
ll n, k;
ll f[maxn][maxn], ff[maxn][maxn];

void mlti(ll a[maxn][maxn], ll b[maxn][maxn])
{
    ll temp[maxn][maxn];
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++)
        {
            temp[i][j] = 0;
            for (int l = 1; l <= k; l++)
                temp[i][j] = (temp[i][j] + a[l][j] * b[i][l]) % tt;
        }
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= k; j++)
            a[i][j] = temp[i][j];
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= k; i++)
        f[i][1] = 1;
    for (int i = 1; i <= k; i++)
        ff[1][i] = 1;
    for (int i = 1; i <= k - 1; i++)
        ff[i + 1][i] = 1;
    n -= k;
    while (n > 0)
    {
        if (n & 1)
            mlti(f, ff);
        mlti(ff, ff);
        n >>= 1;
    }
    cout << f[1][1] % tt << endl;
}