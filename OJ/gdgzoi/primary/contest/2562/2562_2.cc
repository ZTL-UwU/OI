#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

const int MAX_N = 1e7 + 20;
const int MAX_T = 1e5 + 10;

std::vector<int> prime;

bool is_double_prime[MAX_N];
bool is_prime[MAX_N];
int num[MAX_N];

int l[MAX_T];
int r[MAX_T];

void linear_sieve(int border)
{
    std::fill(is_prime, is_prime + MAX_N - 5, true);
    is_prime[0] = false;
    is_prime[1] = false;

    for (int i = 2; i <= border; i++)
    {
        if (is_prime[i])
            prime.emplace_back(i);

        for (std::size_t j = 0; j < prime.size() && i * prime[j] <= border; j++)
        {
            is_prime[i * prime[j]] = false;
            if (i % prime[j] == 0)
                break;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    int max = -1;
    for (int i = 0; i < t; i++)
    {
        std::cin >> l[i] >> r[i];
        max = std::max(max, std::max(l[i], r[i]));
    }

    linear_sieve(max + 10);

    for (int i : prime)
    {
        for (int j : prime)
        {
            if (i * j >= MAX_N)
                break;

            is_double_prime[i * j] = true;
        }
    }

    for (int i = 2; i < max + 10; i++)
        num[i] = num[i - 1] + is_prime[i] + is_double_prime[i];

    for (int i = 0; i < t; i++)
        std::cout << num[r[i]] - num[l[i] - 1] << "\n";
    return 0;
}
