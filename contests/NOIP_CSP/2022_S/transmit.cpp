#include <iostream>
#include <vector>
#include <cstdio>

const long long INF = 1800000000000000000;
const int MAX_N = 2e5 + 10;
const int MAX_LOG = 30;

long long a[MAX_N];
int lgg[MAX_N];
int depth[MAX_N];
int fa[MAX_N][MAX_LOG];
std::vector<int> g[MAX_N];

void get_fa(int u)
{
	for (int v : g[u])
	{
		if (v != fa[u][0])
		{
			fa[v][0] = u;
			for (int i = 1; i < MAX_LOG; i++)
				fa[v][i] = fa[fa[v][i - 1]][i - 1];
			depth[v] = depth[u] + 1;
			get_fa(v);
		}
	}
}

int get_lca(int u, int v)
{
	if (depth[u] < depth[v])
		std::swap(u, v);

	while (depth[u] > depth[v])
		u = fa[u][lgg[depth[u] - depth[v]]];
		
	if (u == v)
		return u;

	for (int i = MAX_LOG - 1; i >= 0; i--)
	{
		int uu = fa[u][i];
		int vv = fa[v][i];
		if (uu != vv)
		{
			u = uu;
			v = vv;
		}
	}
	
	return fa[u][0];
}

int main()
{
	std::freopen("transmit.in", "r", stdin);
	std::freopen("transmit.out", "w", stdout);

	std::ios::sync_with_stdio(false);
	std::cout.tie(0);
	std::cin.tie(0);	
	int n, q, k;
	std::cin >> n >> q >> k;

	lgg[0] = -1;
	for (int i = 1; i < MAX_N; i++)
		lgg[i] = lgg[i / 2] + 1;
	
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
		
	for (int i = 0; i < n - 1; i++)
	{
		int u, v;
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	depth[0] = -1;
	get_fa(1);
	
	for (int i = 0; i < q; i++)
	{
		int u, v;
		std::cin >> u >> v;
		const int lca = get_lca(u, v);
		
		std::vector<long long> qu;
		std::vector<long long> qv;
		
		while (depth[u] >= depth[lca])
		{
			long long min = INF;
			for (long long i : qu)
				min = std::min(min, i);
			qu.push_back(a[u] + (min == INF ? 0 : min));

			if (qu.size() > k + 1)
				qu.erase(qu.begin());
			u = fa[u][0];
		}
		
		while (depth[v] >= depth[lca])
		{
			long long min = INF;
			for (long long i : qv)
				min = std::min(min, i);
			qv.push_back(a[v] + (min == INF ? 0 : min));

			if (qv.size() > k + 1)
				qv.erase(qv.begin());
			v = fa[v][0];
		}
		
		long long min = INF;
		for (size_t i = 0; i < qu.size(); i++)
		{
			for (size_t j = 0; j < qv.size(); j++)
			{
				if (i == qu.size() - 1 && j == qv.size() - 1)
					min = std::min(min, qu[i] + qv[j] - a[lca]);
				else if (qu.size() - i - 1 + qv.size() - j - 1 <= k)
					min = std::min(min, qu[i] + qv[j]);
			}
		}
		
		std::cout << min << "\n";
	}
	return 0;
}
