#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;
vector<int> p;
bool prime(int x)
{
    for (int i = 2; i <= sqrt(x); i++)
        if (x % i == 0)
            return false;
    return true;
}
void get_prime(int maxn)
{
    for (int i = 2; i <= maxn; i++)
        if (prime(i))
            p.push_back(i);
}
int dp[1000];
int main()
{
    int n;
    cin >> n;
    get_prime(n);
    dp[0] = 1;
    for (int i = 0; i < p.size(); i++)
        for (int j = p[i]; j <= n; j++)
            dp[j] += dp[j - p[i]];
    cout << dp[n];
    return 0;
}