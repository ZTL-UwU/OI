#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

const int MOD = 9901;
using i64 = long long;

i64 q_pow(i64 a, int b)
{
    i64 res = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b /= 2;
    }

    return res;
}

bool is_prime(int n)
{
    for (int i = 2; i <= std::sqrt(n); i++)
        if (n % i == 0)
            return false;
    return true;
}

int main()
{
    int a, b;
    std::cin >> a >> b;

    std::vector<std::pair<int, int>> fac;
    for (int i = 2; i <= std::sqrt(a); i++)
    {
        if (is_prime(i) && a % i == 0)
        {
            fac.emplace_back(i, 0);
            while (a % i == 0)
            {
                a /= i;
                fac.back().second++;
            }
            fac.back().second *= b;
        }
    }
    if (a != 1)
        fac.emplace_back(a, b);

    i64 ans = 1;
    for (auto f : fac)
    {
        i64 res = (q_pow(f.first, f.second + 1) - 1) % MOD;
        res = res * q_pow(f.first - 1, MOD - 2) % MOD;
        ans = ans * res % MOD;
    }

    std::cout << ans;
    return 0;
}