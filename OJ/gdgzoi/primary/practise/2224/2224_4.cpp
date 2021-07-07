#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
using namespace std;
int main()
{
    long long n;
    cin >> n;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            cout << n / i << "\n";
            return 0;
        }
    }
    return 0;
}