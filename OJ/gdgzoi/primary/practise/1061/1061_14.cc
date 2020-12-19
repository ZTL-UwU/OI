#include <iostream>
#include <vector>

const int MAX_N = 2e6 + 10;

std::vector<int> prime;
int min_p[MAX_N];
int cnt[MAX_N];

inline void get_prime(int max_n)
{
    for (int i = 2; i <= max_n; i++)
    {
        if (min_p[i] == 0)
        {
            prime.push_back(i);
            min_p[i] = i;
        }

        for (auto j : prime)
        {
            if (i * j > max_n)
                break;

            min_p[i * j] = j;
            if (i % j == 0)
                break;
        }
    }
}

inline long long int quick_power(long long int a, int n, int mod)
{
    long long int res = 1;

    while (n > 0)
    {
        if (n % 2 == 1)
            res = (res * a) % mod;

        a = (a * a) % mod;
        n /= 2;
    }

    return res;
}

/*
 *      2n(2n - 1)...(n + 2)
 * Hn = --------------------
 *               n!
 */

int main()
{
    int n, mod;
    std::cin >> n >> mod;

    get_prime(2 * n);

    for (int i = 2; i <= n; i++)
        cnt[i] = -1;
    for (int i = n + 2; i <= 2 * n; i++)
        cnt[i] = 1;

    for (int i = 2 * n; i >= 2; i--)
    {
        if (min_p[i] < i)
        {
            cnt[min_p[i]] += cnt[i];
            cnt[i / min_p[i]] += cnt[i];
        }
    }

    long long int ans = 1;
    for (int i = 2; i <= 2 * n; i++)
        if (min_p[i] == i)
            ans = (ans * quick_power(i, cnt[i], mod)) % mod;

    std::cout << ans;
    return 0;
}