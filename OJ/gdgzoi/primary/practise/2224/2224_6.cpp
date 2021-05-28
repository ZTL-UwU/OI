#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;
const int MAXN = 1000100;
bool is_prime[MAXN];
vector<int> prime;
void init_prime(int size)
{
    for (int i = 0; i < MAXN; i++)
        is_prime[i] = 1;
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
    int n;
    scanf("%d", &n);
    init_prime(1000010);
    for (int i = 0; i < prime.size() && prime[i] <= n; i++)
    {
        int k = 1;
        int cnt = 0;
        while (pow(prime[i], k) <= n)
        {
            cnt += n / pow(prime[i], k);
            k++;
        }
        printf("%d %d\n", prime[i], cnt);
    }
    return 0;
}