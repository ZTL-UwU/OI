#include <unordered_map>
#include <iostream>
#include <vector>
#include <cmath>

const int ERATOSTHENES_SIEVE_BORDER = 1.7e6;
const int MOD = 998244353;

std::unordered_map<long long int, long long int> dus_sieved_f_sum;
long long int eratosthenes_sieved_f_sum[ERATOSTHENES_SIEVE_BORDER + 10];

void linear_sieve()
{
    eratosthenes_sieved_f_sum[1] = 1;
    for (int i = 1; i <= ERATOSTHENES_SIEVE_BORDER / 2; i++)
        for (int j = i * 2; j <= ERATOSTHENES_SIEVE_BORDER; j += i)
            eratosthenes_sieved_f_sum[j] = (eratosthenes_sieved_f_sum[i] + eratosthenes_sieved_f_sum[j]) % MOD;

    for (int i = 2; i <= ERATOSTHENES_SIEVE_BORDER; i++)
        eratosthenes_sieved_f_sum[i] = (eratosthenes_sieved_f_sum[i] + eratosthenes_sieved_f_sum[i - 1]) % MOD;
}

long long int Dus_sieve(long long int n)
{
    if (n <= ERATOSTHENES_SIEVE_BORDER)
        return eratosthenes_sieved_f_sum[n];
    if (dus_sieved_f_sum[n] != 0)
        return dus_sieved_f_sum[n];

    long long int res = 1;
    for (long long int l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        res = (res + (r - l + 1) * Dus_sieve(n / l) % MOD) % MOD;
    }

    return dus_sieved_f_sum[n] = res;
}

int main()
{
    linear_sieve();

    long long int n;
    std::cin >> n;

    std::cout << Dus_sieve(n);
    return 0;
}