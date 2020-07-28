#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
const int MAXN = 2000;
void dfs(int u, int fa)
{
    dp[u][1] = 1;
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i];
        if (v != fa)
        {
            dfs(v, u);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i ++)
    {
        int u, k;
        cin >> u >> k;
        for (int j = 0; j < k; j ++)
        {
            int v;
            cin >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }
    dfs(1, -1);
    cout << n - max(dp[1][0], dp[1][1]) << endl;
    return 0;
}