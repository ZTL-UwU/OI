#include <algorithm>
#include <iostream>
#include <cstdio>

const int MAX_N = 2.5e7;
const int MAX_Q = 1e7;

bool table[MAX_N];
int ans[MAX_N];

int main()
{
	std::freopen("number.in", "r", stdin);
	std::freopen("number.out", "w", stdout);

	for (int i = 1; i < MAX_N; i++)
	{
		if (!table[i])
		{
			int tmp = i;
			bool flag = false;
			while (tmp)
			{
				if (tmp % 10 == 7)
				{
					flag = true;
					break;
				}
				tmp /= 10;
			}

			if (flag)
			{
				for (int j = 1; i * j < MAX_N; j++)
					table[i * j] = true;
			}
		}
	}

	for (int i = 1; i <= MAX_Q; i++)
	{
		if (table[i])
			ans[i] = -1;
		else
		{
			for (int j = i + 1; j < MAX_N; j++)
			{
				if (!table[j])
				{
					ans[i] = j;
					break;
				}
			}
		}
	}

	int t;
	std::scanf("%d", &t);

	int x;
	for (int _i = 0; _i < t; _i++)
	{
		std::scanf("%d", &x);
		std::printf("%d\n", ans[x]);
	}

	return 0;
}
