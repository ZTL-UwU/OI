#include <iostream>
#include <vector>
using namespace std;
vector<int> prime;
bool vis[100000010];
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
    int m, n;
    cin >> m >> n;
    get_prime(n);
    int ans = 0;
    for (int i = m; i <= n; i++)
        if (!vis[i])
            ans++;
    cout << ans;
    return 0;
}