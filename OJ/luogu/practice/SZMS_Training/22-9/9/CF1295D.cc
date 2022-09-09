#include <iostream>

using i64 = long long;

i64 phi(i64 n)
{
    i64 ans = n;
    for (i64 i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            ans = ans / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    }

    if (n > 1)
        ans = ans / n * (n - 1);
    return ans;
}

i64 gcd(i64 a, i64 b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main()
{
    int t;
    std::cin >> t;

    for (int i = 0; i < t; i++)
    {
        i64 a, m;
        std::cin >> a >> m;

        std::cout << phi(m / gcd(a, m)) << "\n";
    }
    return 0;
}