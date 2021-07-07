#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 2e6 + 10;
priority_queue<int, vector<int>, greater<int>> pq[MAXN];
vector<int> tree[MAXN];
int son[MAXN];
bool in[MAXN];
int c[MAXN];
int ans = 0;
int n, m;
inline void solve(int u)
{
    if (!tree[u].size())
        return;
    for (int i = 0; i < tree[u].size(); i++)
    {
        int v = tree[u][i];
        solve(v);
        pq[u].push(c[v]);
        son[u] += son[v];
    }
    while (!pq[u].empty())
    {
        int vw = pq[u].top();
        pq[u].pop();
        if (m >= son[u] - 1 + c[u] + vw)
        {
            son[u]--;
            c[u] += vw;
            ans++;
        }
    }
}
int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &c[i]);
    for (int i = 1; i <= n; i++)
    {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++)
        {
            int s;
            scanf("%d", &s);
            if (s != i)
            {
                in[s] = true;
                tree[i].push_back(s);
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (!in[i])
            solve(i);
    printf("%d", ans);
    return 0;
}