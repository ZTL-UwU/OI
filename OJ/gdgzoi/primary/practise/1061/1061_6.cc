#include <iostream>
#include <cstring>
#include <cstdio>
#include <ostream>
#include <vector>
#include <cmath>

const int MAX_SQRT_N = 3.5e4;
const int MOD = 999911659;

long long int factorial[MAX_SQRT_N];
bool is_prime[MAX_SQRT_N];
std::vector<int> prime;

inline void get_prime(int max_num)
{
    std::memset(is_prime, true, sizeof(is_prime));

    is_prime[0] = false;
    is_prime[1] = false;

    for (int i = 2; i <= max_num; i++)
    {
        if (is_prime[i])
            prime.push_back(i);

        for (auto p : prime)
        {
            if (i * p > max_num)
                break;

            is_prime[i * p] = false;

            if (i % p == 0)
                break;
        }
    }
}

inline long long int quick_power(long long int a, int n)
{
    long long int ans = 1;

    while (n != 0)
    {
        if (n % 2 == 1)
            ans = (ans * a) % MOD;

        a = (a * a) % MOD;
        n >>= 1;
    }

    return ans;
}

inline long long int c(int n, int m)
{
    return ((factorial[n] * quick_power(factorial[m], MOD - 2) % MOD) * quick_power(factorial[n - m], MOD - 2)) % MOD;
}

inline long long int lucas(int n, int m)
{
    if (m == 0)
        return 1;
    return (c(n % MOD, m % MOD) * lucas(n / MOD, m / MOD)) % MOD;
}

inline void get_factorial(int max_num)
{
    factorial[0] = 1;
    for (int i = 1; i <= max_num; i++)
        factorial[i] = (factorial[i - 1] * i) % MOD;
}

int main()
{
    int n, g;
    std::cin >> n >> g;

    get_prime(std::sqrt(n));
    get_factorial(MAX_SQRT_N - 10);

    int p_factor = 0;
    size_t last = 0;
    while (n > 1)
    {
        for (size_t i = last; i < prime.size(); i++)
        {
            if (n % prime[i] == 0)
            {
                n /= prime[i];
                p_factor++;
                last = i;

                break;
            }
        }
    }

    long long int ans = 0;
    for (int i = 1; i <= p_factor; i++)
        ans = (ans + lucas(p_factor - 1, i - 1)) % MOD;

    std::cout << quick_power(g, ans);
    return 0;
}