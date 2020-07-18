#include <iostream>
#include <math.h>
using namespace std;
int main()
{
    unsigned long long n;
    cin >> n;
    for (int k = 2; k <= sqrt(n); k ++)
    {
        if (n % k == 0)
        {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}