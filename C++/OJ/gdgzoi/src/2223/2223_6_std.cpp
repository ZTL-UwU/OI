#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

long long t, a, b;

long long f[15][15],shu[15];

void init()
{
    memset(f, 0, sizeof(f));
    for (int i = 0; i <= 9; i++)
        f[1][i] = 1;
    for (int i = 2; i <= 10; i++)
        for (int j = 0; j <= 9; j++)
            for (int k = 0; k <= 9; k++)
                if (abs(j - k) >= 2)
                    f[i][j] += f[i - 1][k];
}

long long solve(long long x)
{
    memset(shu, 0, sizeof(shu));
    if (x == 0)
        return 0;
    long long k = 0,ans = 0;
    while (x)
    {
        shu[++k] = x % 10;
        x /= 10;
    }
    for (int i = 1; i <= k - 1; i++)
        for (int j = 1; j <= 9; j++)
            ans += f[i][j];
    for (int i = 1; i < shu[k]; i++)
        ans += f[k][i];
    for (int i = k - 1; i >= 1; i--)
    {
        for (int j = 0; j <= shu[i] - 1; j++)
            if (abs(j - shu[i + 1]) >= 2)
                ans += f[i][j];
        if (abs(shu[i + 1] - shu[i]) < 2)
            break;
        if (i == 1)
            ans += 1;
    }
    return ans;
}

int main()
{
    scanf("%lld%lld", &a, &b);
    init();
    printf("%lld", solve(b) - solve(a - 1));

    while (1);
    return 0;
}