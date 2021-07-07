#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;
const int MAXN = 1000010;
const int MOD = 1e9 + 7;
bool is_prime[MAXN];
vector<int> prime;
long long ans = 1;
void init_prime(int size)
{
    for (int i = 0; i < MAXN; i++)
        is_prime[i] = true;
    for (int i = 2; i <= size; i++)
    {
        if (is_prime[i])
        {
            prime.push_back(i);
            for (int j = i * 2; j <= size; j += i)
                is_prime[j] = false;
        }
    }
}
int main()
{
    while (1)
        ;
    int n;
    cin >> n;
    init_prime(n);
    for (int i = 0; i < prime.size(); i++)
    {
        int p = prime[i];
        int cnt = 0;
        int k = 1;
        while (pow(p, k) <= n)
        {
            cnt += n / pow(p, k);
            k++;
        }
        ans *= cnt * 2 + 1;
        ans %= MOD;
    }
    cout << ans;
    return 0;
}