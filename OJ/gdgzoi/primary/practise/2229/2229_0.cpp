#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
const ll MAXN = 1000;
ll a[MAXN][MAXN];
ll b[MAXN][MAXN];
struct Mat
{
    ll col = MAXN, row = MAXN;
    ll (*m)[MAXN] = new ll[MAXN][MAXN];
};
Mat mult(Mat a, Mat b)
{
    Mat res;
    memset(res.m, 0, sizeof(res.m));
    for (ll k = 0; k < b.col; ++k)
    {
        for (ll i = 0; i < a.col; ++i)
        {
            if (a.m[i][k] == 0)
                continue;
            for (ll j = 0; j < b.row; ++j)
                res.m[i][j] += ((a.m[i][k] % MOD) * (b.m[k][j] % MOD) + MOD) % MOD;
        }
    }
    return res;
}
int main()
{
    ll n, p, m;
    cin >> n >> p >> m;
    for (ll i = 0; i < n; i++)
        for (ll j = 0; j < p; j++)
            cin >> a[i][j], a[i][j] += MOD, a[i][j] %= MOD;
    for (ll i = 0; i < p; i++)
        for (ll j = 0; j < m; j++)
            cin >> b[i][j], b[i][j] += MOD, b[i][j] %= MOD;
    Mat m1, m2, res;
    m1.col = n;
    m1.row = p;
    m2.col = p;
    m2.row = m;
    m1.m = a;
    m2.m = b;
    res.m = mult(m1, m2).m;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
            cout << (res.m[i][j] + MOD) % MOD << " ";
        cout << "\n";
    }
    return 0;
}