#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
const int MAXN = 60000;
int dfn[MAXN];
int low[MAXN];
bool instack[MAXN];
vector<int> g[MAXN];
int tt;
stack<int> s;
int col;
int color[MAXN];
int num[MAXN];
int out[MAXN];
void tarjan(int u)
{
    dfn[u] = low[u] = ++ tt;
    s.push(u);
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i];
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!color[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        ++ col;
        int v = -1;
        do
        {
            v = s.top();
            s.pop();
            color[v] = col;
            num[col] ++;
        } while (u != v);
    }
}
int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i ++)
	{
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
	}
    for (int i = 1; i <= n; i ++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i ++)
    {
        for (int j = 0; j < g[i].size(); j ++)
        {
            int v = g[i][j];
            if (color[i] != color[v]) out[color[i]] ++;
        }
    }
    int ans = 0;
    int tmp = 0;
    for (int i = 1; i <= col; i ++)
        if (!out[i]) {ans = num[i]; tmp ++;}
    if (tmp == 1) cout << ans;
    else cout << "0";
	return 0;
}