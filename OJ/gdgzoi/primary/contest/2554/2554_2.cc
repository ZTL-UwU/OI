#include <iostream>
#include <vector>
#include <cmath>
#include <set>

const int SHIFT = 10;
const int MAX_SQRT = 1e7 + 1000 + SHIFT;

bool not_prime[MAX_SQRT];
std::vector<int> prime;

bool is_prime(long long num)
{
    for (int i = 2; i <= std::sqrt(num); i++)
        if (num % i == 0)
            return false;
    return true;
}

void linear_sieve(int border)
{
    prime.reserve(6e5);

    not_prime[0] = true;
    not_prime[1] = true;
    for (int i = 2; i <= border; i++)
    {
        if (!not_prime[i])
            prime.emplace_back(i);

        for (std::size_t j = 0; j < prime.size() && i * prime[j] <= border; j++)
        {
            not_prime[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
        }
    }
}

unsigned long long quick_pow(unsigned long long a, int n)
{
    if (a > 1e7)
    {
        if (n == 0)
            return 1;
        return a;
    }

    unsigned long long res = 1;

    while (n > 0)
    {
        if (n % 2 == 1)
            res *= a;
        a *= a;
        n /= 2;
    }

    return res;
}

std::vector<unsigned long long> prime_factor;
std::set<unsigned long long> factor;
int factor_cnt[MAX_SQRT];

void dfs(int step, int last, unsigned long long fac)
{
    if (fac != 1)
        factor.insert(fac);

    if (last == (int)prime_factor.size() - 1)
        return;

    for (int i = 0; i <= factor_cnt[last + 1]; i++)
        dfs(step + i, last + 1, fac * quick_pow(prime_factor[last + 1], i));
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    unsigned long long n;
    std::cin >> n;
    linear_sieve(std::sqrt(n) + 1000);

    auto n_tmp = n;
    while (n_tmp % 2 == 0)
        n_tmp /= 2;

    if (is_prime(n_tmp))
    {
        prime_factor.push_back(n_tmp);
        factor_cnt[prime_factor.size() - 1]++;
    }

    for (auto p : prime)
    {
        if (n_tmp % p == 0)
            prime_factor.emplace_back(p);
        while (n_tmp % p == 0)
        {
            factor_cnt[prime_factor.size() - 1]++;
            n_tmp /= p;
        }
    }

    if (is_prime(n))
    {
        std::cout << 1 << " " << n - 1;
        return 0;
    }

    dfs(0, -1, 1);

    std::cout << factor.size() << " ";
    for (auto fac : factor)
        std::cout << (n / fac) * (fac - 1) << " ";
    return 0;
}