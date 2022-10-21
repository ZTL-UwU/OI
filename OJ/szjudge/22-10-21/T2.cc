#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

const int MAX_N = 5e5 + 10;
const int INF = 0x7fffffff;

using vit = std::vector<int>::iterator;
using vec = std::vector<int>;
using std::abs;

vec a;
vec gap;
vec sorted;
int msg = INF; // min sort gap
int inserted[MAX_N];

const vit i2it(vec& v, size_t dis)
{
	vit it = v.begin();
	std::advance(it, dis);
	return it;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);

	int n, m;
	std::cin >> n >> m;
	
	a.resize(n);
	for (int i = 0; i < n; i++)
	{
		std::cin >> a[i];
		if (i > 0)
			gap.push_back(abs(a[i] - a[i - 1]));
	}

	sorted = a;
	std::sort(sorted.begin(), sorted.end());
	for (std::size_t i = 1; i < sorted.size(); i++)
		msg = std::min(msg, abs(sorted[i] - sorted[i - 1]));

	std::sort(gap.begin(), gap.end());

	for (int i = 0; i < m; i++)
	{
		std::string op;
		std::cin >> op;
		
		if (op == "INSERT")
		{
			int x, k;
			std::cin >> x >> k;
			x--;

			gap.erase(std::lower_bound(
				gap.begin(), gap.end(),
				abs(a[x + inserted[x]] - a[x + inserted[x] + 1])
			));
			
			gap.insert(std::lower_bound(
				gap.begin(), gap.end(),
				abs(k - a[x + inserted[x]])
			), abs(k - a[x + inserted[x]]));

			gap.insert(std::lower_bound(
				gap.begin(), gap.end(),
				abs(k - a[x + inserted[x] + 1])
			), abs(k - a[x + inserted[x] + 1]));

			const auto pos = std::lower_bound(sorted.begin(), sorted.end(), k);
			if (pos != sorted.end())
			{
				msg = std::min(msg, abs(k - *(pos - 1)));
				msg = std::min(msg, abs(k - *pos));
			}
			else
				msg = std::min(msg, abs(k - *(pos - 1)));
			sorted.insert(pos, k);

			a.insert(i2it(a, x + inserted[x]) + 1, k);
			inserted[x]++;
		}
		else if (op == "MIN_GAP")
			std::cout << gap.front() << "\n";
		else
			std::cout << msg << "\n";
	}
	return 0;
}