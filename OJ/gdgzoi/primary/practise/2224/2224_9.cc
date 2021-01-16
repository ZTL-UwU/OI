#include <iostream>
#include <vector>
using namespace std;
vector<int> prime;
bool vis[1000100];
void get_prime(int maxn)
{
    vis[0] = 1;
    vis[1] = 1;
    for (int i = 2; i <= maxn; i++)
    {
        if (!vis[i])
            prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= maxn; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
int main()
{
    get_prime(1000100);
    int k;
    while (cin >> k)
    {
        if (k == 1)
        {
            printf("0\n");
        }
        for (int i = prime.size() - 1; i >= 0; i--)
        {
            if (k >= prime[i] && k % prime[i] == 0)
            {
                printf("%d\n", i + 1);
                break;
            }
        }
    }
    return 0;
}