#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
const ll MAXN = 500;
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
    for (ll k = 0; k < b.col; ++ k)
    {
        for (ll i = 0; i < a.col; ++ i)
        {
            if (a.m[i][k] == 0) continue;
            for (ll j = 0; j < b.row; ++ j)
                res.m[i][j] += a.m[i][k] * b.m[k][j];
        }
    }
    return res;
}
int main()
{
    ll n, p, m;
    cin >> n >> p;
    for (ll i = 0; i < n; i ++)
        for (ll j = 0; j < p ; j ++)
            cin >> a[i][j];
    cin >> m;
    for (ll i = 0; i < p; i ++)
        for (ll j = 0; j < m; j ++)
            cin >> b[i][j];
    Mat m1, m2, res;
    m1.col = n;
    m1.row = p;
    m2.col = p;
    m2.row = m;
    m1.m = a;
    m2.m = b;
    res.m = mult(m1, m2).m;
    for (ll i = 0; i < n; i ++)
    {
        for (ll j = 0; j < m; j ++)
            cout << res.m[i][j] << " ";
        cout << "\n";
    }
    return 0;
}