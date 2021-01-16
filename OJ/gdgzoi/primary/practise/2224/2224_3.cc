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
    int a, b;
    while (cin >> a >> b)
    {
        if (a == 0 && b == 0)
            return 0;
        bool flag = true;
        for (int i = a; i <= b; i++)
        {
            if (vis[i * i + i + 41])
            {
                flag = false;
                cout << "Sorry\n";
                break;
            }
        }
        if (flag)
        {
            cout << "OK\n";
        }
    }
    return 0;
}