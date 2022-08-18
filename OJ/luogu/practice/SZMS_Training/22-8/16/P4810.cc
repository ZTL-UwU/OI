#include <unordered_set>
#include <iostream>
#include <vector>
#include <stack>

const int MAX_N = 3e5 + 10;
std::vector<std::vector<int>> sv;

int comp(const std::vector<int>& s1, const std::vector<int>& s2)
{
	int ans = 0;

	for (int i = 0; i < s1.size(); i++)
	{
		const auto tmp = std::lower_bound(s2.begin(), s2.end(), s1[i]);
		if (tmp != s2.end() && *tmp == s1[i])
			ans++;
		else
			break;

		int j = i + 1;
		while (s1[j] == s1[i])
			j++;
		i = j - 1;
	}

	return ans;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int n;
	std::cin >> n;
	sv.push_back(std::vector<int>());

	for (int i = 1; i <= n; i++)
	{
		char op;
		std::cin >> op;
		std::vector<int> new_stack;

		if (op == 'a')
		{
			int v;
			std::cin >> v;
			new_stack = sv[v];

			new_stack.push_back(i);
		}
		else if (op == 'b')
		{
			int v;
			std::cin >> v;
			new_stack = sv[v];

			std::cout << new_stack.back() << "\n";
			new_stack.pop_back();
			new_stack.shrink_to_fit();
		}
		else if (op == 'c')
		{
			int v, w;
			std::cin >> v >> w;
			new_stack = sv[v];

			std::cout << comp(sv[v], sv[w]) << "\n";
		}

		sv.push_back(new_stack);
	}

	return 0;
}