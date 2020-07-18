#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
struct Mat
{
    ll m[3][3];
};
Mat mult(Mat a, Mat b)
{
    Mat res;
    memset(res.m, 0, sizeof(res.m));
    for (ll k = 0; k < 3; ++ k)
    {
        for (ll i = 0; i < 3; ++ i)
        {
            if (a.m[i][k] == 0) continue;
            for (ll j = 0; j < 3; ++ j)
                res.m[i][j] += ((a.m[i][k] % MOD) * (b.m[k][j] % MOD)) % MOD;
        }
    }
}
Mat pow(Mat a, ll k)
{
    Mat res;
    for (ll i = 0; i < 3; i ++)
        for (ll j = 0; j < 3; j ++)
            res.m[i][j] = (i == j);
    while (k)
    {
        if (k & 1) res = mult(res, a);
        a = mult(a, a);
        k >>= 1;
    }
    return res;
}
int main()
{
    Mat start;
    Mat list;
    memset(start.m, 0, sizeof(start.m));
    memset(list.m, 0, sizeof(list.m));
    list.m[0][0] = list.m[0][2] = list.m[1][0] = list.m[2][1] = start.m[0][0] = start.m[1][0] = start.m[2][0] = 1;
    ll t;
    scanf("%lld", &t);
    while (t --)
    {
        ll n;
        scanf("%lld", &n);
        if (n <= 3)
        {
            puts("1");
            continue;
        }
        n --;
        Mat ans = mult(pow(list, n - 1), start);
        cout << ans.m[0][0] % MOD << "\n";
    }
    return 0;
}