#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
using namespace std;
const int MAXN = 30010;
vector<int> g[MAXN];
vector<int> ans;
queue<int> q;
int in[MAXN];
void init()
{
    for (int i = 0; i < MAXN; i ++) g[i].clear();
    ans.clear();
    while (!q.empty()) q.pop();
    memset(in, 0, sizeof(in));
}
int main()
{
    int t;
    cin >> t;
    while (t --)
    {
        init();
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i ++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            in[v] ++;
        }
        for (int i = 1; i <= n; i ++) if (in[i] == 0) q.push(i);
        while (!q.empty())
        {
            int u = q.front();
            ans.push_back(u);
            q.pop();
            for (int i = 0; i < g[u].size(); i ++)
            {
                int v = g[u][i];
                in[v] --;
                if (!in[v]) q.push(v);
            }
        }
        for (int i = 0; i < ans.size(); i ++) cout << ans[i] << " ";
        cout << "\n";
    }
    return 0;
}