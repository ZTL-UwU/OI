#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
typedef long long ll;
const ll MOD = 10000;
const ll MAXN = 2;
struct Mat
{
    ll m[MAXN][MAXN];
};
Mat mult(Mat a, Mat b)
{
    Mat res;
    memset(res.m, 0, sizeof(res.m));
    for (ll k = 0; k < 2; ++k)
    {
        for (ll i = 0; i < 2; ++i)
        {
            if (a.m[i][k] == 0)
                continue;
            for (ll j = 0; j < 2; ++j)
                res.m[i][j] += ((a.m[i][k] % MOD) * (b.m[k][j] % MOD) + MOD) % MOD;
        }
    }
    return res;
}
Mat pow(Mat a, ll b)
{
    Mat res;
    for (ll i = 0; i < MAXN; ++i)
        for (ll j = 0; j < MAXN; ++j)
            res.m[i][j] = (i == j);
    while (b)
    {
        if (b & 1)
            res = mult(res, a);
        a = mult(a, a);
        b >>= 1;
    }
    return res;
}
int main()
{
    Mat start;
    Mat fibonacci;
    fibonacci.m[0][0] = fibonacci.m[0][1] = fibonacci.m[1][0] = 1;
    fibonacci.m[1][1] = 0;
    start.m[0][0] = start.m[1][0] = 1;
    ll n;
    while (1)
    {
        scanf("%lld", &n);
        if (n < 0)
            return 0;
        if (n == 0)
        {
            cout << "0\n";
            continue;
        }
        if (n == 1)
        {
            cout << "1\n";
            continue;
        }
        if (n == 2)
        {
            cout << "1\n";
            continue;
        }
        n--;
        Mat ans;
        // ans = pow(fibonacci, n - 1);
        // for (int i = 0; i < MAXN; i ++)
        // {
        //     for (int j = 0; j < MAXN; j ++)
        //         cout << ans.m[i][j] << " ";
        //     cout << "\n";
        // }
        ans = mult(pow(fibonacci, n - 1), start);
        ll out = (ans.m[0][0] + MOD) % MOD;
        printf("%lld\n", out);
    }
    return 0;
}