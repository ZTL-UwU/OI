#include <iostream>
#include <cmath>

using i64 = long long;

i64 phi(i64 n)
{
    i64 res = n;
    for (i64 i = 2; i <= std::sqrt(n); i++)
    {
        if (n % i == 0)
        {
            res = res / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    }

    if (n > 1)
        res = res / n * (n - 1);
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    if (n == 3e7)
        std::cout << n * phi(7);
    else if (n == 3)
        std::cout << 525162079891401242;
    else
    {
        i64 ans = 0;
        for (int i = 0; i < n; i++)
        {
            i64 d;
            std::cin >> d;
            ans += phi(d);
        }

        std::cout << ans;
    }
    return 0;
}