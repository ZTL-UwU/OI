#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>

using namespace std;
const int MAXN = 1e5 + 10;
int degree[MAXN];
int odd[MAXN];
int fa[MAXN];
int n, m;
int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    fa[fx] = fy;
}
int main()
{
    while (cin >> n >> m)
    {
        if (m == 0)
        {
            cout << "0\n";
            continue;
        }
        memset(degree, 0, sizeof(degree));
        memset(odd, 0, sizeof(odd));
        for (int i = 0; i < n + 5; i++)
            fa[i] = i;
        int ans = 0;
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            degree[u]++;
            degree[v]++;
            merge(u, v);
        }
        for (int i = 1; i <= n; i++)
            if (degree[i] % 2)
                odd[find(i)]++;
        for (int i = 1; i <= n; i++)
        {
            if (fa[i] == i && !odd[i] && degree[i])
                ans++;
            ans += odd[i] / 2;
        }
        cout << ans << "\n";
    }
    return 0;
}