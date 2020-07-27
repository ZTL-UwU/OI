#include <bits/stdc++.h>
using namespace std;
int main()
{
    int k, a;
    while (cin >> k)
    {
        for (a = 1; a <= 65; a++)
            if ((18 + k * a) % 65 == 0)
            {
                cout << a << endl;
                break;
            }
        if (a > 65)
            cout << "no" << endl;
    }
    return 0;
}