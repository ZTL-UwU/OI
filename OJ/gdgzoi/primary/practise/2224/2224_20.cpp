#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;
const int INF = 0x7fffffff;
const int MAXN = 1e5 + 10;
const int SQRT = 32000;
bool is_prime[SQRT];
vector<int> g[MAXN];
vector<int> prime;
vector<int> fac;
bool has_fac[MAXN];
int maxn = -INF;
bool vis[MAXN];
int a[MAXN];
int n;
void init_prime()
{
    for (int i = 2; i < SQRT; i++)
        is_prime[i] = true;
    for (int i = 2; i < SQRT; i++)
    {
        if (is_prime[i])
        {
            prime.push_back(i);
            for (int j = i * 2; j < SQRT; j += i)
                is_prime[j] = false;
        }
    }
}
int dfs(int u)
{
    vis[u] = true;
    int tmp = 0;
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (has_fac[v] && !vis[v])
            tmp = max(tmp, dfs(v));
    }
    return tmp + 1;
}
int search()
{
    int tmp = -INF;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < fac.size(); i++)
        if (!vis[i])
            tmp = max(tmp, dfs(i));
    return tmp;
}
int main()
{
    init_prime();
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < prime.size(); i++)
    {
        memset(has_fac, 0, sizeof(has_fac));
        fac.clear();
        int p = prime[i];
        for (int i = 0; i < n; i++)
        {
            if (!(a[i] % p))
            {
                has_fac[i] = true;
                fac.push_back(i);
            }
        }
        maxn = max(maxn, search());
    }
    cout << maxn;
    return 0;
}