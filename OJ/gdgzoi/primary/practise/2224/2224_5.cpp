#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;
const int INF = 0x7fffffff;
bool is_prime[60000];
vector<int> prime;
void init_prime(int size)
{
    for (int i = 2; i <= size; i++)
    {
        if (is_prime[i])
        {
            prime.push_back(i);
            for (int j = 2 * i; j <= size; j += i)
                is_prime[j] = false;
        }
    }
}
int main()
{
    for (int i = 0; i < 60000; i++)
        is_prime[i] = 1;
    init_prime(50000);
    int l, r;
    while (~scanf("%d %d", &l, &r))
    {
        int cnt = 0;
        int maxn_l = INF, maxn_r = INF;
        int minn_l = INF, minn_r = INF;
        int maxn = -INF;
        int minn = INF;
        int last_prime = 0;
        for (int i = l; i <= r; i++)
        {
            if (i == 1)
                continue;
            bool is_p = true;
            for (int p = 0; p < prime.size() && prime[p] < i; p++)
            {
                if (i % prime[p] == 0)
                {
                    is_p = false;
                    break;
                }
            }
            if (is_p && last_prime)
            {
                if (i - last_prime > maxn)
                {
                    maxn = i - last_prime;
                    maxn_l = last_prime;
                    maxn_r = i;
                }
                if (i - last_prime < minn)
                {
                    minn = i - last_prime;
                    minn_l = last_prime;
                    minn_r = i;
                }
            }
            if (is_p)
                cnt++, last_prime = i;
        }
        if (cnt < 2)
            printf("There are no adjacent primes.\n");
        else
            printf("%d,%d are closest, %d,%d are most distant.\n", minn_l, minn_r, maxn_l, maxn_r);
    }
    return 0;
}