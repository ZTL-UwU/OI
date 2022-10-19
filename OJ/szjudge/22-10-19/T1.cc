#include <iostream>
#include <cmath>

using i64 = long long;

i64 pow(i64 a, i64 b)
{
    i64 res = 1;
    while (b > 0)
    {
        if (b % 2 == 0)
            res *= a;
        a *= a;
        b /= 2;
    }

    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; i++)
    {
        i64 n;
        std::cin >> n;
        if (n == 1)
            std::cout << 0 << "\n";
        else
        {
            n = std::ceil(n / 2.0);
            const i64 tmp = pow(2, std::ceil(std::log2(n))) - 1;
            std::cout << tmp << "\n";
        }
    }
    return 0;
}