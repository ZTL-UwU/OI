#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
using namespace std;
int phi(int n)
{
    int res = n;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            res = res / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        res = res / n * (n - 1);
    return res;
}
int main()
{
    int n;
    cin >> n;
    cout << phi(n) << "\n";
    return 0;
}