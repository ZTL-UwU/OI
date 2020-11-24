#include <iostream>

inline unsigned long long int slow_mult(unsigned long long int a, unsigned long long int b, unsigned long long int mod)
{
    unsigned long long int ans = 0;

    while (b != 0)
    {
        if (b % 2 == 1)
            ans = (ans + a) % mod;

        a = (a + a) % mod;
        b >>= 1;
    }

    return ans;
}

int main()
{
    unsigned long long int a, b, p;
    std::cin >> a >> b >> p;

    std::cout << slow_mult(a, b, p);
    return 0;
}