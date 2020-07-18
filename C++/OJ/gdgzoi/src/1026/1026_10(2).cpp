#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 30000;
int num[MAXN];
int w[MAXN];
int v[MAXN];
int dp[MAXN];
int n;
int main()
{
    int tmp, val;
    cin >> tmp >> val;
    for (int i = 0; i < tmp; i ++)
    {
        int _num, _w, _v;
        cin >> _num >> _w >> _v;
        int cnt = 1;
        while (_num - cnt >= 0)
        {
            _num -= cnt;
            v[n] = _v * cnt;
            w[n ++] = _w * cnt;
            cnt *= 2;
        }
        v[n] = _v * _num;
        w[n ++] = _w * _num;
    }
    for (int i = 0; i < n; i ++)
        for (int j = val; j >= w[i]; j --)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    cout << dp[val];
    return 0;
}