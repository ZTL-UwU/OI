#include <iostream>

long long int fast_pow(long long int b, int p, int mod)
{
    long long int res = 1;

    while (p != 0)
    {
        if (p % 2 == 1)
            res = (res * b) % mod;
        b = (b * b) % mod;

        p /= 2;
    }

    return res;
}

int main()
{
    long long int b;
    int p, k;
    std::cin >> b >> p >> k;

    std::cout << b << "^" << p << " mod " << k << "=" << fast_pow(b, p, k);
    return 0;
}