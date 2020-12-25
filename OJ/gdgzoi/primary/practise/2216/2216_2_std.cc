#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;
#define inf 99999999
#define pi acos(-1.0)
#define maxn 10040
int value[maxn], du[maxn], vis[maxn], n;
ll sum1, num1;

struct edge
{
    int to, next, len;
} e[200050];
int first[maxn];
int q[1111111];

void topu()
{
    int i, j, front, rear, x, xx, v;
    front = 1;
    rear = 0;
    for (i = 1; i <= n; i++)
    {
        if (du[i] <= 1)
        {
            rear++;
            q[rear] = i;
            vis[i] = 1;
        }
    }
    while (front <= rear)
    {
        x = q[front];
        front++;
        for (i = first[x]; i != -1; i = e[i].next)
        {
            v = e[i].to;
            if (vis[v])
                continue;
            du[v]--;
            if (du[v] <= 1)
            {
                rear++;
                q[rear] = v;
                vis[v] = 1;
            }
        }
    }
}

void dfs(int root)
{
    int i, j, v;
    vis[root] = 1;
    num1++;
    sum1 += value[root];
    for (i = first[root]; i != -1; i = e[i].next)
    {
        v = e[i].to;
        if (!vis[v])
        {
            dfs(v);
        }
    }
}

int main()
{
    int m, i, j, T, tot, c, d;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (i = 1; i <= n; i++)
        {
            scanf("%d", &value[i]);
        }
        tot = 0;
        memset(first, -1, sizeof(first));
        memset(du, 0, sizeof(du));
        memset(vis, 0, sizeof(vis));
        for (i = 1; i <= m; i++)
        {
            scanf("%d%d", &c, &d);
            du[c]++;
            du[d]++;
            tot++;
            e[tot].next = first[c];
            e[tot].to = d;
            first[c] = tot;

            tot++;
            e[tot].next = first[d];
            e[tot].to = c;
            first[d] = tot;
        }
        topu();
        ll sum = 0;
        for (i = 1; i <= n; i++)
        {
            if (vis[i])
                continue;
            sum1 = 0;
            num1 = 0;
            dfs(i);
            if (num1 & 1)
                sum += sum1;
        }
        printf("%lld\n", sum);
    }
    return 0;
}
