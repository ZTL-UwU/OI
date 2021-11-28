#include <iostream>
#include <cstdio>
#include <vector>

const int MAX_N = 2e5 + 10;
int fruit[MAX_N];

int main()
{
	std::freopen("fruit.in", "r", stdin);
	std::freopen("fruit.out", "w", stdout);

	int n;
	std::scanf("%d", &n);

	for (int i = 1; i <= n; i++)
		std::scanf("%d", &fruit[i]);

	while (true)
	{
		bool found = false;
		for (int i = 1; i <= n; i++)
		{
			if (fruit[i] == -1)
				continue;

			found = true;
			std::cout << i << " ";
			int k = i + 1;
			while (k <= n && (fruit[k] == fruit[i] || fruit[k] == -1))
				k++;
			fruit[i] = -1;
			i = k - 1;
		}

		std::cout << "\n";
		if (!found)
			break;
	}

	return 0;
}