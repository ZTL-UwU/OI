#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

const int MAX_N = 1e4;

int a[MAX_N];

int main()
{
	std::freopen("sort.in", "r", stdin);
	std::freopen("sort.out", "w", stdout);

	int n, q;
	std::scanf("%d %d", &n, &q);

	std::vector<int> num;
	std::vector<int> id;
	id.resize(n);
	for (int i = 1; i <= n; i++)
	{
		std::scanf("%d", &a[i]);
		num.push_back(a[i]);
	}

	std::sort(num.begin(), num.end());
	for (int i = 1; i <= n; i++)
	{
		for (int j = std::lower_bound(num.begin(), num.end(), a[i]) - num.begin(); j < std::upper_bound(num.begin(), num.end(), a[i]) - num.begin(); j++)
		{
			if (!id[j])
			{
				id[j] = i;
				break;
			}
		}
	}

	// for (int i = 0; i < num.size(); i++)
	// 	std::cout << num[i] << ' ' << id[i] << "\n";

	for (int _i = 0; _i < q; _i++)
	{
		int op;
		std::scanf("%d", &op);

		if (op == 1)
		{
			int x, v;
			std::scanf("%d %d", &x, &v);

			for (int i = std::lower_bound(num.begin(), num.end(), a[x]) - num.begin(); i < std::upper_bound(num.begin(), num.end(), a[x]) - num.begin(); i++)
			{
				if (id[i] == x)
				{
					num.erase(num.begin() + i);
					const int dis = std::lower_bound(num.begin(), num.end(), v + 1) - num.begin();
					// std::cout << dis << "--\n";
					num.insert(num.begin() + (std::lower_bound(num.begin(), num.end(), v + 1) - num.begin()), v);
					id.erase(id.begin() + i);
					id.insert(id.begin() + dis, x);
					a[x] = v;
					break;
				}
			}

			// std::cout << "\n";
			// for (int i = 0; i < num.size(); i++)
			// 	std::cout << num[i] << ' ' << id[i] << "\n";
			// std::cout << "\n";
		}
		else if (op == 2)
		{
			int x;
			std::scanf("%d", &x);

			// std::cout << a[x] << " " << std::lower_bound(num.begin(), num.end(), a[x]) - num.begin() << " " << std::upper_bound(num.begin(), num.end(), a[x]) - num.begin() << "   ";

			for (int i = std::lower_bound(num.begin(), num.end(), a[x]) - num.begin(); i < std::upper_bound(num.begin(), num.end(), a[x]) - num.begin(); i++)
			{
				if (id[i] == x)
				{
					std::printf("%d\n", i + 1);
					break;
				}
			}
		}
	}

	return 0;
}