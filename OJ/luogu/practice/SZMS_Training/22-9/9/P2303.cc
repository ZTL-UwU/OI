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

int main()
{
    i64 n;
    std::cin >> n;

    i64 ans = 0;
    i64 i;
    for (i = 1; i * i < n; i++)
        if (n % i == 0)
            ans += i * phi(n / i) + (n / i) * phi(i);
    
    if (i * i == n)
        ans += i * phi(i);

    std::cout << ans;
    return 0;
}