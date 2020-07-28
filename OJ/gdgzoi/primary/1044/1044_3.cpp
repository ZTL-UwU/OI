#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
const int MAXN = 10000;
using namespace std;
int n, m;
vector<int> g[MAXN];
int dfn[MAXN];
int low[MAXN];
bool iscp[MAXN];
bool vis[MAXN];
int tt;
void init()
{
	for (int i = 0; i < MAXN; i ++) g[i].clear();
	n = 0; m = 0; tt = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(iscp, 0, sizeof(iscp));
}
void tarjan(int u, int fa)
{
	dfn[u] = low[u] = ++ tt;
	int ch = 0;
	for (int i = 0; i < g[u].size(); i ++)
	{
		int v = g[u][i];
		if (!dfn[v])
		{
			tarjan(v, u);
			ch ++;
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) iscp[u] = true;
		}
		else low[u] = min(low[u], dfn[v]);
	}
	if (fa == -1 && ch == 1) iscp[u] = false;
}
void dfs(int u, int cp)
{
	vis[u] = true;
	for (int i = 0; i < g[u].size(); i ++)
	{
		int v = g[u][i];
		if (!vis[v] && v != cp) dfs(v, cp);
	}
}
int check(int cp)
{
	int res = 0;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i ++)
	{
		if (!vis[i])
		{
			res ++;
			dfs(i, cp);
		}
	}
	return res;
}
int main()
{
	int t = 0;
	while (1)
	{
		t ++;
		init();
		int u, v, k = 0;
		while (1)
		{
			cin >> u;
			if (!k && !u) return 0;
			k ++;
			if (!u) break;
			cin >> v;
			n = max(n, max(u, v));
			m ++;
			g[u].push_back(v);
			g[v].push_back(u);
		}
		for (int i = 1; i <= n; i ++)
			if (!dfn[i]) tarjan(i, -1);
		cout << "Network #" << t << '\n';
		bool flag = true;
		for (int i = 1; i <= n; i ++)
		{
			if (iscp[i])
			{
				flag = false;
				int subg = check(i);
				cout << "  SPF node " << i << " leaves " << subg << " subnets\n";
			}
		}
		if (flag) cout << "  No SPF nodes\n";
		cout << '\n';
	}
	return 0;
}