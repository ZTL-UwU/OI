#include <iostream>

const long double INF = 0x7fffffff;

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main()
{
    int a, b, l;
    std::cin >> a >> b >> l;

    const auto ab = (long double)a / (long double)b;

    auto res = INF;
    int res_a = a;
    int res_b = b;

    for (int i = 1; i <= l; i++)
    {
        for (int j = 1; j <= l; j++)
        {
            if (gcd(i, j) == 1)
            {
                const auto a1b1 = (long double)i / (long double)j;
                if (ab <= a1b1 && a1b1 < res)
                {
                    res = a1b1;
                    res_a = i;
                    res_b = j;
                }
            }
        }
    }

    std::cout << res_a << " " << res_b;
    return 0;
}