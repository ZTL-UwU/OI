#include <iostream>
#include <string.h>
using namespace std;
const int MAXN = 3e5 + 10;
bool certened[MAXN];
bool vis[MAXN];
int size[MAXN];
int fa[MAXN];
int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
    int fx = fa[x];
    int fy = fa[y];
    fa[fx] = fy;
}
int main()
{
    for (int i = 0; i < MAXN; i++)
        fa[i] = i;
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int x;
            scanf("%d", &x);
            certened[find(x)] = true;
            size[find(x)]++;
        }
        else
        {
            int x, y;
            scanf("%d %d", &x, &y);
            size[y] += size[x];
            bool flag = false;
            if (certened[find(x)] || certened[find(y)])
                flag = true;
            merge(x, y);
            if (flag && !certened[find(y)])
            {
                certened[find(y)] = true;
                size[y]++;
            }
        }
        long long ans = 0;
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++)
        {
            if (certened[find(i)] && !vis[find(i)])
            {
                ans += size[find(i)];
                vis[find(i)] = true;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}