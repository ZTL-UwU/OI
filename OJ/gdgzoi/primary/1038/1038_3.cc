#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 10;
vector<int> tree[MAXN];
int sit[MAXN];
int siz[MAXN];
int num[MAXN];
int num_id = 0;
int n;
inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int val)
{
    while (x <= n)
    {
        sit[x] += val;
        x += lowbit(x);
    }
}
inline int query(int x)
{
    int sum = 0;
    while (x > 0)
    {
        sum += sit[x];
        x -= lowbit(x);
    }
    return sum;
}
inline void dfs(int u, int fa)
{
    num[u] = ++num_id;
    siz[u] = 1;
    for (int i = 0; i < tree[u].size(); i++)
    {
        int v = tree[u][i];
        if (v != fa)
        {
            dfs(v, u);
            siz[u] += siz[v];
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        add(i, 1);
    int q;
    cin >> q;
    while (q--)
    {
        char type;
        int x;
        cin >> type >> x;
        if (type == 'C')
        {
            x = num[x];
            if (query(x) - query(x - 1) == 1)
                add(x, -1);
            else
                add(x, 1);
        }
        else
            cout << query(num[x] + siz[x] - 1) - query(num[x] - 1) << '\n';
    }
    return 0;
}