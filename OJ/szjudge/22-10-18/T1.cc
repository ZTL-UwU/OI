#include <iostream>

const int MOD = 998244352;
using i64 = long long;

i64 qpow(i64 a, i64 b)
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
	
	i64 ans;
	std::cin >> ans;

	for (int i = 1; i < n; i++)
	{
		int a;
		std::cin >> a;
		if (a == 0)
		{
			ans = 1;
			break;
		}
		if (a == 1)
			break;

		ans = qpow(ans, a);
	}

	std::cout << ans;
	return 0;
}