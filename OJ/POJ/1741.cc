#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
const int MAXN = 1e4 + 10;
struct data
{
    int v, w;
};
vector<data> tree[MAXN];
vector<int> a;
bool vis[MAXN];
int maxx[MAXN];
int dis[MAXN];
int siz[MAXN];
int root, ans;
int n, k;
inline void get_root(int u, int fa)
{
    maxx[u] = 0;
    siz[u] = 1;
    for (int i = 0; i < tree[u].size(); i++)
    {
        int v = tree[u][i].v;
        if (v != fa && !vis[v])
        {
            get_root(v, u);
            siz[u] += siz[v];
            maxx[u] = max(maxx[u], siz[v]);
        }
    }
    maxx[u] = max(maxx[u], n - maxx[u]);
    if (!root || maxx[u] < maxx[root])
        root = u;
}
inline void get_dis(int u, int fa)
{
    a.push_back(dis[u]);
    for (int i = 0; i < tree[u].size(); i++)
    {
        int v = tree[u][i].v;
        int w = tree[u][i].w;
        if (v != fa && !vis[v])
        {
            dis[v] = dis[u] + w;
            get_dis(v, u);
        }
    }
}
inline int calc(int u, int w)
{
    a.clear();
    dis[u] = w;
    get_dis(u, 0);
    sort(a.begin(), a.end());
    int l = 0;
    int r = a.size() - 1;
    int res = 0;
    while (l < r)
    {
        if (a[l] + a[r] <= k)
        {
            res += r - l;
            l++;
        }
        else
            r--;
    }
    return res;
}
inline void solve(int u)
{
    ans += calc(u, 0);
    vis[u] = true;
    for (int i = 0; i < tree[u].size(); i++)
    {
        int v = tree[u][i].v;
        int w = tree[u][i].w;
        if (!vis[v])
        {
            ans -= calc(v, w);
            n = siz[v];
            root = 0;
            get_root(v, u);
            solve(root);
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (1)
    {
        cin >> n >> k;
        if (n == 0 && k == 0)
            return 0;
        for (int i = 0; i < MAXN; i++)
            tree[i].clear();
        for (int i = 0; i < n - 1; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            tree[u].push_back((data){v, w});
            tree[v].push_back((data){u, w});
        }
        ans = 0;
        root = 0;
        memset(vis, 0, sizeof(vis));
        get_root(1, 0);
        solve(root);
        cout << ans << "\n";
    }
    return 0;
}