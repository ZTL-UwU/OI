#include <iostream>

using i64 = long long;
const int MOD = 1e9 + 7;

i64 pow(i64 a, i64 b)
{
    i64 res = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        b /= 2;
    }

    return res;
}

int main()
{
    i64 n;
    std::cin >> n;
    std::cout << (((n - 1) % MOD) * pow(2, n - 1)) % MOD + 1;
    return 0;
}