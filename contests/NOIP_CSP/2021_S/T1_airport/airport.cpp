#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>

struct event
{
	int time;
	int plane;
	bool is_land;
	bool is_national;
};

std::unordered_map<int, bool> pos; // true -> bridge  |  false -> field
std::vector<event> ev;

int main()
{
	std::freopen("airport.in", "r", stdin);
	std::freopen("airport.out", "w", stdout);

	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);

	int n, m1, m2;
	// std::scanf("%d %d %d", &n, &m1, &m2);
	std::cin >> n >> m1 >> m2;

	for (int i = 0; i < m1 +  m2; i++)
	{
		int in, out;
		// std::scanf("%d %d", &in, &out);
		std::cin >> in >> out;

		ev.emplace_back(event{in, i, true, i < m1});
		ev.emplace_back(event{out, i, false, i < m1});
	}

	if (n >= m1 + m2)
	{
		// std::printf("%d", n);
		std::cout << n;
		return 0;
	}

	std::sort(ev.begin(), ev.end(), [](event e1, event e2) -> bool { return e1.time < e2.time; });
	int ans = 0;
	for (int i = 0; i <= n; i++)
	{
		int cnt1 = 0;
		int cnt2 = 0;
		int res = 0;

		for (auto e : ev)
		{
			if (e.is_national)
			{
				if (e.is_land && cnt1 < i)
				{
					pos[e.plane] = true;
					cnt1++;
					res++;
				}
				else if (e.is_land) { pos[e.plane] = false; }
				else if (!e.is_land && pos[e.plane]) { cnt1--; }
			}
			else if (!e.is_national)
			{
				if (e.is_land && cnt2 < n - i)
				{
					pos[e.plane] = true;
					cnt2++;
					res++;
				}
				else if (e.is_land) { pos[e.plane] = false; }
				else if (!e.is_land && pos[e.plane]) { cnt2--; }
			}
		}

		ans = std::max(ans, res);
	}

	// std::printf("%d", ans);
	std::cout << ans;

	return 0;
}