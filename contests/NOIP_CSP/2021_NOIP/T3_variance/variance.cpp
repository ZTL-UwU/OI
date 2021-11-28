#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>

const int MAX_N = 1e4 + 10;
const int INF = 0x7fffffff;
const int MAX_DEPTH = 4e5;

std::map<std::vector<int>, bool> seen;
std::vector<std::vector<int>> seq;
std::vector<int> src;
int a[MAX_N];

int sqr(int x) { return x * x; }

void bfs()
{
	std::queue<std::vector<int>> q;
	q.push(src);

	int depth = 0;
	while (!q.empty())
	{
		const auto u = q.front();
		seq.emplace_back(u);
		q.pop();

		seen[u] = true;
		++depth;
		if (depth > MAX_DEPTH)
		{
			while (!q.empty())
				q.pop();
			continue;
		}

		for (std::size_t i = 1; i < u.size() - 1; i++)
		{
			if (u[i - 1] + u[i + 1] - u[i] != u[i])
			{
				std::vector<int> v(u);
				v[i] = u[i - 1] + u[i + 1] - u[i];
				if (!seen[v])
					q.push(v);
			}
		}
	}
}

int main()
{
	std::freopen("variance.in", "r", stdin);
	std::freopen("variance.out", "w", stdout);

	int n;
	std::scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		std::scanf("%d", &a[i]);
		src.emplace_back(a[i]);
	}

	bfs();

	int ans = INF;
	for (auto v : seq)
	{
		int asqr = 0;
		int sum = 0;
		for (auto i : v)
		{
			asqr += sqr(i);
			sum += i;
		}

		ans = std::min(ans, n * asqr - sqr(sum));
	}

	std::printf("%d", ans);
	return 0;
}
