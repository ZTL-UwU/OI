#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;
ll n, k;
struct Mat
{
    ll m[55][55];
};
Mat mult(Mat a, Mat b)
{
    Mat res;
    memset(res.m, 0, sizeof(res.m));
    for (ll l = 0; l < k; ++ l)
    {
        for (ll i = 0; i < k; ++ i)
        {
            if (a.m[i][l] == 0) continue;
            for (ll j = 0; j < k; ++ j)
            {
                res.m[i][j] += ((a.m[i][l] % MOD) * (b.m[l][j] % MOD)) % MOD;
                res.m[i][j] %= MOD;
            }
        }
    }
    return res;
}
Mat pow(Mat a, ll b)
{
    Mat res;
    for (ll i = 0; i < k; i ++)
        for (ll j = 0; j < k; j ++)
            res.m[i][j] = (i == j);
    while (b)
    {
        if (b & 1) res = mult(res, a);
        a = mult(a, a);
        b >>= 1;
    }
    return res;
}
int main()
{
    cin >> n >> k;
    Mat start;
    Mat list;
    memset(start.m, 0, sizeof(start.m));
    memset(list.m, 0, sizeof(list.m));
    for (int i = 0; i < k; i ++) list.m[0][i] = 1;
    for (int i = 0; i < k; i ++) list.m[i + 1][i] = 1;
    for (int i = 0; i < k; i ++) start.m[i][0] = 1;
    if (n <= k)
    {
        puts("1");
        return 0;
    }
    n -= k;
    Mat ans = mult(pow(list, n), start);
    cout << ans.m[0][0] % MOD << "\n";
    return 0;
}