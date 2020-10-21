#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
struct data
{
	int l, r;
    int len()
    {
        return r - l + 1;
    }
};
data request[40000];
int dp[50000];
inline bool cmp(data a, data b)
{
    if (a.r == b.r)
        return a.l < b.l;
	return a.r < b.r;
}
int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> request[i].l >> request[i].r;
	sort(request, request + n, cmp);

	for (int i = 0; i < n; i++)
    {
        dp[i] = request[i].len();
        for (int j = 0; j < i; j++)
        {
            if (request[j].r >= request[i].l)
                break;
            dp[i] = max(dp[i], dp[j] + request[i].len());
        }
    }
	cout << dp[n - 1];
	return 0;
}