#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
using namespace std;
int phi(int n)
{
    int res = n;
    for (int i = 2; i <= sqrt(n); i ++)
    {
        if (n % i == 0)
        {
            res = res / i * (i - 1);
            while (!(n % i)) n /= i;
        }
    }
    if (n > 1) res = res / n * (n - 1);
    return res;
}
int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t ++)
    {
        int n;
        cin >> n;
        int res = 0;
        for (int i = 1; i <= n; i ++) res += phi(i);
        cout << t << " " << n << " " << res * 2 + 1 << "\n";    
    }
    return 0;
}