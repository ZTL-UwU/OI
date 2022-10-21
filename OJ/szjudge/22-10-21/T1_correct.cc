#include <iostream>

using i64 = long long;

int main()
{
	i64 a, x;
	std::cin >> a >> x;
	if (a & x)
		std::cout << -1;
	else
		std::cout << a + x;
	return 0;
}