#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int MAX_N = 1e3 + 10;

struct qdata
{
	int u;
	int ability;
	int score;
};

vector<int> tree[MAX_N];
bool vis[MAX_N];
int fa[MAX_N];
int d[MAX_N];
int c[MAX_N];
int ans = -1;

void dfs(int u)
{
	for (size_t i = 0; i < tree[u].size(); i++)
	{
		const int v = tree[u][i];
		if (v != fa[u])
		{
			fa[v] = u;
			dfs(v);
		}
	}
}

void bfs(const int start, const int k)
{
	queue<qdata> q;
	q.push((qdata){start, k, 0});
	q.push((qdata){start, k - c[start], min((k * 100) / d[start], 100)});

	while (!q.empty())
	{
		const qdata u = q.front();
		q.pop();

		ans = max(ans, u.score);
		for (size_t i = 0; i < tree[u.u].size(); i++)
		{
			const int v = tree[u.u][i];

			if (v != fa[u.u] && u.ability >= c[v])
			{
				q.push((qdata){v, u.ability - c[v], u.score + min((u.ability * 100) / d[v], 100)});
				q.push((qdata){v, u.ability, u.score});
			}
		}
	}
}

int main()
{
	freopen("AC.in", "r", stdin);
	freopen("AC.out", "w", stdout);

	int n, k;
	scanf("%d %d", &n, &k);

	for (int _i = 0; _i < n - 1; _i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		tree[u].push_back(v);
		tree[v].push_back(u);
	}

	for (int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);

		for (int j = 1; j <= a; j++)
			for (int k = 1; k <= a; k++)
				d[i] = (d[i] + (a % j) * (a % k) % 100) % 100;
	}

	for (int i = 1; i <= n; i++)
		scanf("%d", &c[i]);

	dfs(1);
	bfs(1, k);

	printf("%d", ans);
	return 0;
}