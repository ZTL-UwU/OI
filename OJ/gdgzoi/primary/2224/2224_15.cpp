#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;
const int MAXN = 1000010;
bool is_prime[MAXN];
vector<int> prime;
void init_prime(int size)
{
    for (int i = 0; i < MAXN; i ++) is_prime[i] = true;
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
    init_prime(1000001);
    int n;
    while (1)
    {
        scanf("%d", &n);
        if (!n) return 0;
        for (int i = 0; i < prime.size(); i ++)
        {
            int x = prime[i];
            if (x % 2 && is_prime[n - x])
            {
                printf("%d = %d + %d\n", n, x, n - x);
                break;
            }
        }
    }
    return 0;
}