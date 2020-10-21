#include <iostream>
using namespace std;
const int MAXN = 6e3;
const int MOD = 1e4;
long long price[MAXN];
long long days[MAXN];
long long ways[MAXN];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> price[i];
    n++;
    for (int i = 0; i < n; i++)
    {
        days[i] = 1;
        for (int j = 0; j < i; j++)
            if (price[j] > price[i])
                days[i] = max(days[i], days[j] + 1);
        long long last = price[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if (price[j] > price[i] && days[j] + 1 == days[i] && price[j] != last)
            {
                ways[i] = ((ways[i] + MOD) % MOD + (ways[j] + MOD) % MOD + MOD) % MOD;
                last = price[j];
            }
        }
        if (ways[i] < 1)
            ways[i] = 1;
    }
    cout << days[n - 1] - 1 << "\n" << (ways[n - 1] + MOD) % MOD << "\n";
    return 0;
}