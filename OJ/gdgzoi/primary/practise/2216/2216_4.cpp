#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 20010;
vector<int> g[MAXN];
int in[MAXN];
queue<int> q;
bool dfs(int u)
{
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
    }
}
int main()
{
    bool flagg = true;
    bool flagc = true;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        char ch;
        cin >> u >> ch >> v;
        if (ch == '>' || ch == '=')
            g[u].push_back(v), in[v]++;
        if (ch == '<')
            g[v].push_back(u), in[u]++;
    }
    flagc = dfs(0);
    for (int i = 0; i < n; i++)
        if (in[i] == 0)
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        bool flag = true;
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i];
            in[v]--;
            if (!in[v])
            {
                flag = false;
                q.push(v);
            }
        }
        if (flag)
        {
            flagg = false;
            break;
        }
    }
    if (flagg)
        cout << "CONFLICT";
    else
        cout << "OK";
    return 0;
}