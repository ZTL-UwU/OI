#include <iostream>
#include <cstdio>

int main()
{
	std::freopen("shuffle.in", "r", stdin);
	std::freopen("shuffle.out", "w", stdout);
	
	int t;
	std::cin >> t;
	
	for (int _i = 0; _i < t; _i++)
	{
		std::string a, b;
		std::cin >> a >> b;
		
		if (a.front() != b.front() || a.back() != b.back())
		{
			std::cout << "-1\n";
			continue;
		}
		
		if (a == b)
		{
			std::cout << "0\n";
			break;
		}
		
		int u = 1;
		bool first = true;
		int ans = 0;
		bool has_ans = false;
		while (first || u != 1)
		{
			first = false;
			
			if (u % 2 == 0)
				u = u / 2;
			else
				u = a.size() / 2 + u / 2;
			ans++;

			if (b[u] == a[1])
			{
				has_ans = true;
				break;
			}
		}
		
		for (int i = 2; i < a.size(); i++)
		{
			int u = i;
			for (int j = 0; j < ans; j++)
			{
				if (u % 2 == 0)
					u = u / 2;
				else
					u = a.size() / 2 + u / 2;
			}
			
			if (b[u] != a[i])
			{
				has_ans = false;
				break;
			}
		}
		
		if (!has_ans)
			std::cout << "-1\n";
		else
			std::cout << ans << "\n";
	}
	return 0;
}
