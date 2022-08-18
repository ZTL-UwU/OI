#include <algorithm>
#include <iostream>

const int MAX_N = 3e5 + 10;
const int MOD = 1e9 + 7;

double k[MAX_N];

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;

	for (int i = 0; i < n; i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		k[i] = -((double)a / b);
	}

	std::sort(k, k + n);

	long long ans = 0;
	for (int i = 1; i < n - 1; i++)
	{
		long long l_cnt = std::lower_bound(k, k + n, k[i]) - k;
		long long r_cnt = k + n - std::upper_bound(k, k + n, k[i]);

		ans = (ans + l_cnt * r_cnt) % MOD;
	}

	std::cout << ans;
	return 0;
}