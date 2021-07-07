#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <sstream>
using namespace std;
const int MAXN = 1000;
vector<int> g[MAXN];
int dfn[MAXN];
int low[MAXN];
bool iscp[MAXN];
int n;
int tt;
void init()
{
    n = 0;
    tt = 0;
    for (int i = 0; i < MAXN; i++)
        g[i].clear();
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(iscp, 0, sizeof(iscp));
}
void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++tt;
    int ch = 0;
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (!dfn[v])
        {
            tarjan(v, u);
            ch++;
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u])
                iscp[u] = true;
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
    if (fa == -1 && ch == 1)
        iscp[u] = false;
}
int main()
{
    while (1)
    {
        init();
        cin >> n;
        if (!n)
            return 0;
        string s;
        while (getline(cin, s))
        {
            if (s[0] == '0')
                break;
            stringstream ss;
            int u, k;
            ss << s;
            ss >> u;
            while (ss >> k)
            {
                g[u].push_back(k);
                g[k].push_back(u);
            }
        }
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                tarjan(i, -1);
        int num = 0;
        for (int i = 1; i <= n; i++)
            if (iscp[i])
                num++;
        cout << num << "\n";
    }
    return 0;
}