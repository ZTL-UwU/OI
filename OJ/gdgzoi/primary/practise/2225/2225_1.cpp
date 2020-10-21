#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t --)
    {
        int m, n;
        scanf("%d %d", &m, &n);
        if (gcd(n, m) != 1) puts("YES");
        else puts("NO");
    }
    return 0;
}