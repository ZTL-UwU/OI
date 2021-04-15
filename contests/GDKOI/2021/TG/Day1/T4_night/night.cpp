#include <iostream>
#include <cstdio>

int main()
{
	std::freopen("night.in", "r", stdin);
	std::freopen("night.out", "w", stdout);

	long long int n, k, A;
	std::cin >> n >> k >> A;

	if (k == 0)
		std::cout << n + (n - 1) * A;
	return 0;
}
