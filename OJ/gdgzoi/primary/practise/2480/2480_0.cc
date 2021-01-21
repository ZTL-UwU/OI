#include <unordered_map>
#include <iostream>
#include <vector>
#include <cmath>

const int LINEAR_SIEVE_BORDER = 1.665e6; // (2 ^ 31) ^ (2 / 3)

bool not_prime[LINEAR_SIEVE_BORDER];
// std::vector<int> prime;
int prime[LINEAR_SIEVE_BORDER];
int cnt;

std::unordered_map<int, long long int> linear_sieved_phi_sum;
std::unordered_map<int, long long int> dus_sieve_phi_sum;

void linear_sieve()
{
    // prime.reserve(LINEAR_SIEVE_BORDER);

    linear_sieved_phi_sum[1] = 1;

    for (int i = 2; i < LINEAR_SIEVE_BORDER; i++)
    {
        if (not not_prime[i])
        {
            // prime.push_back(i);
            prime[cnt++] = i;
            linear_sieved_phi_sum[i] = i - 1;
        }

        // for (auto p : prime)
        // {
        //     if (i * p >= LINEAR_SIEVE_BORDER)
        //         break;

        //     not_prime[i * p] = true;

        //     if (i % p != 0)
        //         linear_sieved_phi_sum[i * p] = linear_sieved_phi_sum[i] * linear_sieved_phi_sum[p];
        //     else
        //     {
        //         linear_sieved_phi_sum[i * p] = linear_sieved_phi_sum[i] * p;
        //         break;
        //     }
        // }

        for (int j = 0; j < cnt; j++)
        {
            if (i * prime[j] >= LINEAR_SIEVE_BORDER)
                break;

            not_prime[i * prime[j]] = true;

            if (i % prime[j] != 0)
                linear_sieved_phi_sum[i * prime[j]] = linear_sieved_phi_sum[i] * linear_sieved_phi_sum[prime[j]];
            else
            {
                linear_sieved_phi_sum[i * prime[j]] = linear_sieved_phi_sum[i] * prime[j];
                break;
            }
        }
    }

    for (int i = 1; i < LINEAR_SIEVE_BORDER; i++)
        linear_sieved_phi_sum[i] += linear_sieved_phi_sum[i - 1];
}

long long int Dus_sieve(int n)
{
    if (n < LINEAR_SIEVE_BORDER)
        return linear_sieved_phi_sum[n];
    if (dus_sieve_phi_sum[n] != 0)
        return dus_sieve_phi_sum[n];

    long long int res = (1LL * n * (n + 1)) / 2;
    for (long long int l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        res -= (r - l + 1) * Dus_sieve(n / l);
    }

    return dus_sieve_phi_sum[n] = res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    linear_sieve();

    int n;
    while (std::cin >> n)
        std::cout << Dus_sieve(n) << "\n";
    return 0;
}