#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
const int INF = 0x7fffffff;
bool is_prime[60000];
bool is_prime2[500000];
vector<int> prime;
vector<int> prime2;
void init_prime(int size)
{
    for (int i = 0; i < 60000; i ++) is_prime[i] = true;
    for (int i = 2; i <= size; i ++)
    {
        if (is_prime[i])
        {
            prime.push_back(i);
            for (int j = i * 2; j <= size; j += i) is_prime[j] = false;
        }
    }
}
int main()
{
    init_prime(50000);
    int l, r;
    while (~scanf("%d %d", &l, &r))
    {
        memset(is_prime2, 0, sizeof(is_prime2));
        prime2.clear();
        int maxn_l, maxn_r, minn_l, minn_r, maxn = -INF, minn = INF;
        for (int i = 0; i < prime.size(); i ++)
            for (int j = l / prime[i]; j <= r / prime[i]; j ++)
                if (j > 1 && prime[i] * j - l >= 0) is_prime2[j * prime[i] - l] = true;
        for (int i = l; i <= r; i ++) if (!is_prime2[i - l]) prime2.push_back(i);
        for (int i = 1; i < prime2.size(); i ++)
        {
            if (prime2[i] - prime2[i - 1] < minn)
            {
                minn = prime2[i] - prime2[i - 1];
                minn_l = prime2[i - 1];
                minn_r = prime2[i];
            }
            if (prime2[i] - prime2[i - 1] > maxn)
            {
                maxn = prime2[i] - prime2[i - 1];
                maxn_l = prime2[i - 1];
                maxn_r = prime2[i];
            }
        }
        if (prime2.size() < 2) printf("There are no adjacent primes.\n");
        else printf("%d,%d are closest, %d,%d are most distant.\n", minn_l, minn_r, maxn_l, maxn_r);
    }
    return 0;
}