#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;
const int MAXN = 20000;
int dfn[MAXN];
int low[MAXN];
int tt;
stack<int> s;
vector<int> g[MAXN];
int col;
int color[MAXN];
int out[MAXN];
int num[MAXN];
int cnt;
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
    if (dfn[u] == low[u])
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
    int sccs = 0;
    for (int i = 1; i <= col; i ++)
        if (num[i] > 1) sccs ++;
    cout << sccs << endl;
    for (int i = 1; i <= n; i ++)
    {
        for (int j = 0; j < g[i].size(); j ++)
        {
            int v = g[i][j];
            if (color[i] != color[v]) out[color[i]] ++;
        }
    }
    int res = 0;
    vector<int> ans;
    for (int i = 1; i <= col; i ++)
    {
        if (out[i] == 0 && num[i] > 1)
        {
            res ++;
            if (res > 1)
            {
                cout << "-1";
                return 0;
            }
            for (int j = 1; j <= n; j ++)
                if (color[j] == i) ans.push_back(j);
        }
    }
    if (!ans.size())
    {
    	cout << "-1";
    	return 0;
	}
    for (int i = 0; i < ans.size(); i ++) cout << ans[i] << " ";
    return 0;
}