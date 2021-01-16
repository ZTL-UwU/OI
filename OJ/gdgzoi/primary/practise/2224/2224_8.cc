#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
vector<int> prime;
bool vis[1000010];
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
    get_prime(1000000);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        if (!vis[k])
            cout << k - 1 << endl;
        else if (k == 4)
            cout << 2 << endl;
        else
            cout << 0 << endl;
    }
    return 0;
}