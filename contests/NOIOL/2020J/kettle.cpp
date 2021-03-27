#include <iostream>
using namespace std;
const int MAXN = 1e6 + 10;
int sum[MAXN];
int a[MAXN];
int main()
{
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        sum[i] += a[i];
        sum[i + 1] = sum[i];
    }
    if (k + 1 >= n)
    {
        cout << sum[n] << "\n";
        return 0;
    }
    int maxn = sum[k];
    for (int i = k + 1; i < n; i ++)
        maxn = max(maxn, sum[i] - sum[i - k - 1]);
    cout << maxn << "\n";
}