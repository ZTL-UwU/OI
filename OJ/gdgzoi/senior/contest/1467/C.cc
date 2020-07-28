#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
struct data { int v, w; };
const int MAXN = 2e4 + 10;
vector<data> son[MAXN];
vector<data> fa[MAXN];
int depth[MAXN];
int dis[MAXN];
inline int gcd(int n, int m)
{
    if (m == 0)
        return n;
    if (n < m)
    {
        int tmp = n;
        n = m;
        m = tmp;
    }
    return gcd(m, n % m);
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        depth[v] = depth[u] + 1;
        dis[v] = dis[u] + w;
        son[u].push_back((data){v, w});
        fa[v].push_back((data){u, w});
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            int len = 0;
            int u, v;
            if (depth[j] > depth[i])
            {
                u = j;
                v = i;
            }
            else
            {
                u = i;
                v = j;
            }
            bool flag = true;
            while (u != v)
            {
                if (dis[u] < dis[v])
                {
                    flag = false;
                    break;
                }
                len += fa[u][0].w;
                u = fa[u][0].v;
            }
            if (!flag)
                len = dis[i] + dis[j];
            if (!(len % 3))
                ++cnt;
        }
    }
    int tot = n * n;
    cnt = cnt * 2 + n;
    int g = gcd(cnt, tot);
    cnt /= g;
    tot /= g;
    printf("%d/%d", cnt, tot);
    return 0;
}