#include <iostream>
#include <cstdio>

int main()
{
	std::freopen("candy.in", "r", stdin);
	std::freopen("candy.out", "w", stdout);

	int n, l, r;
	std::cin >> n >> l >> r;

	for (int i = 1; i <= r / n; i++)
	{
		const int k = n * i - 1;

		if (l <= k && k <= r)
		{
			std::cout << k % n;
			return 0;
		}
	}

	std::cout << r % n;
	return 0;
}