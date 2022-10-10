#include <iostream>

using i64 = long long;
const int MOD = 1e9 + 7;

i64 pow(i64 a, i64 b)
{
	i64 res = 1;
	while (b > 0)
	{
		if (b % 2 == 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b /= 2;
	}

	return res;
}

int main()
{
	int n;
	std::cin >> n;

	i64 ans = 0;
	for (int i = 3; i <= n; i++)
		ans = (ans + i * pow(2, i - 2) % MOD) % MOD;

	std::cout << ans + 3;
	return 0;
}