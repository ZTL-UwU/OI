#include <unordered_map>
#include <iostream>
#include <vector>
#include <cmath>

const int LINEAR_SIEVE_BORDER = 1.665e6; // (2 ^ 31) ^ (2 / 3)

bool not_prime[LINEAR_SIEVE_BORDER];
int prime[LINEAR_SIEVE_BORDER];
int cnt;

unsigned long long int linear_sieved_phi_sum[LINEAR_SIEVE_BORDER + 10];
std::unordered_map<int, unsigned long long int> dus_sieve_phi_sum;

int linear_sieved_mu_sum[LINEAR_SIEVE_BORDER + 10];
std::unordered_map<int, int> dus_sieve_mu_sum;

void linear_sieve()
{
    linear_sieved_phi_sum[1] = 1;
    linear_sieved_mu_sum[1] = 1;

    for (int i = 2; i < LINEAR_SIEVE_BORDER; i++)
    {
        if (not not_prime[i])
        {
            prime[cnt++] = i;
            linear_sieved_phi_sum[i] = i - 1;
            linear_sieved_mu_sum[i] = -1;
        }

        for (int j = 0; j < cnt; j++)
        {
            if (i * prime[j] >= LINEAR_SIEVE_BORDER)
                break;

            not_prime[i * prime[j]] = true;

            if (i % prime[j] != 0)
            {
                linear_sieved_phi_sum[i * prime[j]] = linear_sieved_phi_sum[i] * linear_sieved_phi_sum[prime[j]];
                linear_sieved_mu_sum[i * prime[j]] = -linear_sieved_mu_sum[i];
            }
            else
            {
                linear_sieved_phi_sum[i * prime[j]] = linear_sieved_phi_sum[i] * prime[j];
                linear_sieved_mu_sum[i * prime[j]] = 0;
                break;
            }
        }
    }

    for (int i = 1; i < LINEAR_SIEVE_BORDER; i++)
    {
        linear_sieved_phi_sum[i] += linear_sieved_phi_sum[i - 1];
        linear_sieved_mu_sum[i] += linear_sieved_mu_sum[i - 1];
    }
}

long long int Dus_sieve_phi(long long int n)
{
    if (n < LINEAR_SIEVE_BORDER)
        return linear_sieved_phi_sum[n];
    if (dus_sieve_phi_sum[n] != 0)
        return dus_sieve_phi_sum[n];

    long long int res = (1ULL * n * (n + 1)) / 2;
    for (long long int l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        res -= 1ULL * (r - l + 1) * Dus_sieve_phi(n / l);
    }

    return dus_sieve_phi_sum[n] = res;
}

int Dus_sieve_mu(long long int n)
{
    if (n < LINEAR_SIEVE_BORDER)
        return linear_sieved_mu_sum[n];
    if (dus_sieve_mu_sum[n] != 0)
        return dus_sieve_mu_sum[n];

    long long int res = 1;
    for (long long int l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        res -= (r - l + 1) * Dus_sieve_mu(n / l);
    }

    return dus_sieve_mu_sum[n] = res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    linear_sieve();

    int T;
    std::cin >> T;

    for (int t = 0; t < T; t++)
    {
        long long int n;
        std::cin >> n;
        std::cout << Dus_sieve_phi(n) << " " << Dus_sieve_mu(n) << "\n";
    }
    return 0;
}
