#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
int main()
{
    long long aa, b;
    cin >> aa >> b;
    long long aaa = aa;
    long long len = 1;
    do
    {
        len *= 10;
        aaa /= 10;
    } while (aaa);
    long long ans = 0;
    for (long long i = 100; i <= 999; i++)
        if ((long long)(i * len + aa) % b == 0)
            ans++;
    cout << ans;
    return 0;
}