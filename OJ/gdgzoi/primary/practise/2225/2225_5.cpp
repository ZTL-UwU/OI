#include <iostream>
#include <stdio.h>
using namespace std;
typedef long long ll;
int main()
{
    // f(1) = 18 + ka
    ll k;
    while (cin >> k)
    {
        for (ll a = 1; a <= 65; a++)
        {
            if ((k * a + 18) % 65 == 0)
            {
                cout << a << "\n";
                break;
            }
            if (a == 64)
            {
                cout << "no\n";
                break;
            }
        }
    }
    return 0;
}