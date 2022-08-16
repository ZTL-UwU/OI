#include <iostream>
#include <cstdio>
#include <deque>

int n;
std::deque<int> a, b;
std::deque<char> route;
std::deque<char> ans;

bool check_palin(std::deque<int> dq)
{
	while (!dq.empty())
	{
		if (dq.front() != dq.back())
			return false;
		dq.pop_front();
		dq.pop_back();
	}

    return true;
}

bool dfs(int step)
{
	if (step == 2 * n)
    {
		if (check_palin(b))
        {
            ans = route;
            return true;
        }
        
        return false;
    }

	const int af = a.front();
	const int ab = a.back();

	a.pop_front();
	b.push_back(af);
	route.push_back('L');
	if (dfs(step + 1))
		return true;
	route.pop_back();
	a.push_front(af);
	b.pop_back();

	a.pop_back();
	b.push_back(ab);
	route.push_back('R');
	if (dfs(step + 1))
		return true;
	route.pop_back();
	a.push_back(ab);
	b.pop_back();

	return false;
}

int main()
{
	std::freopen("palin.in", "r", stdin);
	std::freopen("palin.out", "w", stdout);

	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);

	int t;
	std::cin >> t;

	for (int _i = 0; _i < t; _i++)
	{
		a.clear();
		b.clear();
        ans.clear();
		route.clear();
		std::cin >> n;

		for (int i = 0; i < 2 * n; i++)
		{
			int num;
			std::cin >> num;
			a.push_back(num);
		}

		if (dfs(0))
			for (auto op : ans)
				std::cout << op;
		else
			std::cout << "-1";
		std::cout << "\n";
	}

	return 0;
}