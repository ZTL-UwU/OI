#include <iostream>
#include <memory.h>
using namespace std;

int b[1000005], a[1000005];
bool v[1000005];

int n, m;

void init()
{
    v[1] = 1;
    for (int i = 2; i <= 46340; ++i)
    {
        if (!v[i])
            a[++n] = i;
        for (int j = 2; j <= 46340 / i; ++j)
            v[i * j] = 1;
    }
}

int main()
{
    int x, y, a1, b1, a2, b2, left, right;
    init();
    while (cin >> left >> right)
    {
        memset(v, 0, sizeof(v));
        if (left == 1)
            v[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = left / a[i]; j <= right / a[i]; ++j)
            {
                if (j > 1 && a[i] * j - left < 1000001 && a[i] * j - left >= 0)
                    v[a[i] * j - left] = 1;
            }
        }

        m = 0;

        for (int i = left; i <= right; ++i)
        {
            if (!v[i - left])
                b[++m] = i;
        }

        if (m < 2)
        {
            cout << "There are no adjacent primes." << endl;
            continue;
        }

        x = 0x7fffffff;
        y = 0;

        for (int i = 2; i <= m; ++i)
        {
            int w = b[i] - b[i - 1];
            if (w < x)
            {
                x = w;
                a1 = b[i - 1];
                b1 = b[i];
            }

            if (w > y)
            {
                y = w;
                a2 = b[i - 1];
                b2 = b[i];
            }
        }

        if (!y)
            cout << "There are no adjacent primes." << endl;
        else
            cout << a1 << "," << b1 << " are closest, " << a2 << "," << b2 << " are most distant." << endl;
    }
    return 0;
}
