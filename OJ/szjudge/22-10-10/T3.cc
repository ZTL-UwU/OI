#include <iostream>
#include <vector>
#include <queue>

using i64 = long long;

struct data
{
	int v;
	i64 w;
};

const int MAX_N = 2e5 + 10;
const int INF = 0x7fffffff;

std::vector<data> g[MAX_N];
bool inque[MAX_N];
int vis[MAX_N];
i64 s[MAX_N];

std::vector<i64> min_history;
std::vector<i64> max_history;

void dfs(int u, int w, int key)
{
	s[u] = std::min(s[u], min_history.back() - max_history.back() + w);

	for (data v : g[u])
	{
		if (vis[v.v] < key)
		{
			vis[v.v]++;
			min_history.push_back(std::min(min_history.back(), v.w));
			max_history.push_back(std::max(max_history.back(), v.w));
			dfs(v.v, w + v.w, key);
			vis[v.v]--;
			min_history.pop_back();
			max_history.pop_back();
		}
	}
}

void spfa()
{
	std::queue<int> q;
	q.push(1);
	inque[1] = true;
	s[1] = 0;
	
	while (!q.empty())
	{
		const int u = q.front();
		q.pop();
		inque[u] = false;
		
		for (data v : g[u])
		{
			if (s[v.v] > s[u] + v.w)
			{
				s[v.v] = s[u] + v.w;
				if (!inque[v.v])
				{
					inque[v.v] = true;
					q.push(v.v);
				}
			}
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);

	int n, m;
	std::cin >> n >> m;

	bool same = true;
	int start_w;
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		std::cin >> u >> v >> w;
		
		if (i == 0)
			start_w = w;
		else if (start_w != w)
			same = false;

		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}

	for (int i = 1; i <= n; i++)
		s[i] = INF;

	min_history.push_back(INF);
	max_history.push_back(-INF);
	vis[1] = 1;
	if (n <= 10 && m <= 10)
		dfs(1, 0, 3);
	else if (same)
		spfa();
	else
		dfs(1, 0, 2);

	for (int i = 2; i <= n; i++)
		std::cout << s[i] << " ";
	return 0;
}