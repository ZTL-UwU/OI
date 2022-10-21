#include <iostream>

using i64 = long long;

int main()
{
	i64 a, x;
	std::cin >> a >> x;

	i64 ans = 0;
	bool has_ans = true;
	for (int i = 0; i < 64; i++)
	{
		int ba = a % 2;
		int bx = x % 2;
		
		if (ba == 1 && bx == 0 || ba == 0 && bx == 1)
			ans += 1 << i;
		else if (ba == 1 && bx == 1)
		{
			has_ans = false;
			break;
		}

		a /= 2;
		x /= 2;
	}
	
	if (!has_ans)
		std::cout << "-1";
	else
		std::cout << ans;

	return 0;
}