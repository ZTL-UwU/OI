#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
struct data
{
    int v, w;
};
const int MAXN = 2e4 + 10;
vector<data> tree[MAXN];
vector<int> a;
bool vis[MAXN];
int maxx[MAXN];
int dis[MAXN];
int siz[MAXN];
int mod[3];
int root;
int ans;
int n;
inline int gcd(int n, int m)
{
    if (m == 0)
        return n;
    if (n < m)
        swap(n, m);
    return gcd(m, n % m);
}
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
    if (root == 0 || maxx[u] < maxx[root])
        root = u;
}
inline void get_dis(int u, int fa)
{
    mod[dis[u] % 3]++;
    for (int i = 0; i < tree[u].size(); i++)
    {
        int v = tree[u][i].v;
        int w = tree[u][i].w;
        if (v != fa && !vis[v])
        {
            dis[v] = (dis[u] + w) % 3;
            get_dis(v, u);
        }
    }
}
inline int calc(int u, int w)
{
    mod[0] = mod[1] = mod[2] = 0;
    dis[u] = w % 3;
    get_dis(u, 0);
    return mod[0] * mod[0] + mod[1] * mod[2] * 2;
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
    cin >> n;
    int tot = n * n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        tree[u].push_back((data){v, w});
        tree[v].push_back((data){u, w});
    }
    get_root(1, 0);
    solve(root);
    int g = gcd(ans, tot);
    ans /= g;
    tot /= g;
    cout << ans << "/" << tot;
    return 0;
}