#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
int a[3];
int m[] = { 23, 28, 33 };
int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}
void exgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    int tmp = x;
    x = y;
    y = tmp - (a / b) * y;
}
int main()
{
    int t = 0;
    while (1)
    {
        ++ t;
        int M = 1;
        int lim;
        for (int i = 0; i < 3; i ++) cin >> a[i], M *= m[i];
        cin >> lim;
        if (a[0] < 0) return 0;
        int ans = 0;
        for (int i = 0; i < 3; i ++)
        {
            int Mi = M / m[i];
            int Mi_1, y;
            int g = gcd(Mi, m[i]);
            exgcd(Mi, m[i], Mi_1, y);
            while (Mi_1 < 0) Mi_1 += m[i] / g;
            ans += a[i] * Mi * Mi_1;
        }
        int x = ans % M;
        while (x <= lim) x += 23 * 28 * 33;
        printf("Case %d: the next triple peak occurs in %d days.\n", t, x - lim);
    }
    return 0;
}