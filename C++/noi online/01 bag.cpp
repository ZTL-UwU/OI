#include<iostream>
using namespace std;
int w[1000000];
int v[1000000];
int dp[1000000];
int main()
{
	int val, n;
	cin >> val >> n;
	for (int i = 0; i < n; i ++) cin >> w[i] >> v[i];
	for (int i = 0; i < n; i ++)
		for (int j = val; j >= w[i]; j --)
			dp[j] = max(dp[j - w[i]] + v[i], dp[j]);
	cout << dp[val];
	return 0;
}