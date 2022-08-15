#include <iostream>
#include <cstring>

const int MOD = 1e9 + 7;
const int MAX_N = 1e4 + 10;

long long dp[2][MAX_N];

int main()
{
	int n, h_dummy;
	std::cin >> n >> h_dummy;
	
	if (h_dummy > 0)
	{
		std::cout << 0;
		return 0;
	}

	bool cur = false;
	dp[cur][0] = 1;

	for (int i = 2; i <= n; i++)
	{
		cur = !cur;
		std::memset(dp[cur], 0, sizeof(dp[cur]));

		int h;
		std::cin >> h;

		const int lim = i <= n / 2 ? i - 1 : n - i;
		if (h > lim)
		{
			std::cout << 0;
			return 0;
		}
		else if (h != -1)
		{
			dp[cur][h] = ((h > 0 ? dp[!cur][h - 1] : 0) + dp[!cur][h] + dp[!cur][h + 1]) % MOD;
		}
		else
		{
			for (int j = 0; j <= lim; j++)
				dp[cur][j] = ((j > 0 ? dp[!cur][j - 1] : 0) + dp[!cur][j] + dp[!cur][j + 1]) % MOD;
		}
	}

	std::cout << dp[cur][0] % MOD;
	return 0;
}
