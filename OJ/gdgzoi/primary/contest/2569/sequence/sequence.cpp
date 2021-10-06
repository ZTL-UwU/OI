#include <iostream>
#include <cstdio>
#include <cmath>

const int MAX_N = 2e7 + 10;

long long F[MAX_N] = {0, 1, 1, 2, 2, 4};

long long f(long long d)
{
	if (d < MAX_N && F[d])
		return F[d];

	long long res = 0;

	for (int i = 1; i <= std::sqrt(d); i++)
	{
		if (d % i == 0)
		{
			if (!F[i])
				F[i] = f(i);
			res += F[i];

			if (d / i != i && i != 1)
			{
				if (d / i < MAX_N)
				{
					if (!F[d / i])
						F[d / i] = f(d / i);
					res += F[d / i];
				}
				else
					res += f(d / i);
			}
		}
	}

	if (d < MAX_N)
		F[d] = d - res;
	return d - res;
}

int main()
{
	std::freopen("sequence.in", "r", stdin);
	std::freopen("sequence.out", "w", stdout);

	int n;
	std::scanf("%d", &n);

	long long ans = 0;
	for (int i = 0; i < n; i++)
	{
		long long d;
		std::scanf("%lld", &d);

		ans += f(d);
	}

	std::printf("%lld", ans);
	return 0;
}