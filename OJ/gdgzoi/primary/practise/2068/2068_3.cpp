#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
const int MAXN = 1000;
struct data
{
	int v, w;
};
int dp[MAXN][MAXN];
vector<data> g[MAXN];
void dfs(int u, int fa, int m)
{
	for (int i = 0; i < g[u].size(); i ++)
	{
		int v = g[u][i].v, w = g[u][i].w;
		if (v != fa)
		{
			dfs(v, u, m - 1);
			for (int j = m; j >= 1; j --)
			{
				for (int k = j - 1; k >= 1; k --)
				{
					dp[u][j] = max(dp[u][j], dp[u][k] + dp[v][j - k] + w);
				}
			}
		}
	}
}
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i ++)
	{
		int v, w;
		cin >> v >> w;
		g[i].push_back((data){v, w});
		g[v].push_back((data){i, w});
	}
	dfs(0, -1, m + 1);
	cout << dp[0][m + 1];
	return 0;
}
