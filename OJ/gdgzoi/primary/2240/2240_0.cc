#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
const int MAXN = 2e4 + 10;
vector<int> tree[MAXN];
int maxx[MAXN];
int siz[MAXN];
int root;
int n;
inline void get_root(int u, int fa)
{
    siz[u] = 1;
    maxx[u] = 0;
    for (int i = 0; i < tree[u].size(); i++)
    {
        int v = tree[u][i];
        if (v != fa)
        {
            get_root(v, u);
            siz[u] += siz[v];
            maxx[u] = max(maxx[u], siz[v]);
        }
    }
    maxx[u] = max(maxx[u], n - siz[u]);
    if (!root || (maxx[u] < maxx[root] || (maxx[u] == maxx[root] && u < root)))
        root = u;
}
inline void init()
{
    for (int i = 0; i < MAXN; i++)
        tree[i].clear();
    memset(maxx, 0, sizeof(maxx));
    memset(siz, 0, sizeof(siz));
    root = 0;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        init();
        cin >> n;
        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }
        get_root(1, 0);
        cout << root << " " << maxx[root] << "\n";
    }
    return 0;
}