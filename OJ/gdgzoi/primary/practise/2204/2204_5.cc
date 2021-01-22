#include <iostream>
#include <numeric>
#include <vector>

const int MAX_N = 1e7;

long long int phi_sum[MAX_N + 10];
bool not_prime[MAX_N + 10];
std::vector<int> prime;

void linear_sieve(int max_n)
{
    phi_sum[1] = 1;

    for (int i = 2; i <= max_n; i++)
    {
        if (not not_prime[i])
        {
            phi_sum[i] = i - 1;
            prime.push_back(i);
        }

        for (auto p : prime)
        {
            if (i * p > max_n)
                break;

            not_prime[i * p] = true;

            if (i % p != 0)
                phi_sum[i * p] = phi_sum[i] * (p - 1);
            else
            {
                phi_sum[i * p] = phi_sum[i] * p;
                break;
            }
        }
    }

    for (int i = 1; i <= max_n; i++)
        phi_sum[i] += phi_sum[i - 1];
}

int main()
{
    int n;
    std::cin >> n;

    linear_sieve(n);

    std::cout << std::accumulate(prime.begin(), prime.end(), (long long int)0,
                                 [n](long long int sum, int p) { return sum + phi_sum[n / p] * 2 - 1; });
    return 0;
}