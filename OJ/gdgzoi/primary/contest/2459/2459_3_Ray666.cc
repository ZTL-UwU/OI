#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

map<int, int> head;

struct node
{
    int v;
    int next;
} a[4000001];

int f[201], m[201], tot = 0, n, ans = 0;
bool check[20000001];

void add(int x, int y)
{
    a[++tot].v = y;
    a[tot].next = head[x];
    head[x] = tot;
}

void dfs(int x, int y, int z)
{
    if (x > n / 2 - 2)
    {
        if (y >= 0)
            add(y, z);
        return;
    }
    dfs(x + 1, y + m[x], z + f[x]);
    dfs(x + 1, y - m[x], z + f[x]);
    dfs(x + 1, y, z);
}

void work(int x, int y, int z)
{
    for (int i = head[y]; i; i = a[i].next)
    {
        if (!check[a[i].v + z])
            check[a[i].v + z] = true, ans++;
    }
    if (x > n)
        return;
    work(x + 1, y + m[x], z + f[x]);
    work(x + 1, y - m[x], z + f[x]);
    work(x + 1, y, z);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &m[i]);

    f[1] = 1;
    for (int i = 2; i <= n; i++)
        f[i] = f[i - 1] * 2;

    dfs(1, 0, 0);
    work(n / 2 - 1, 0, 0);

    ans--;
    printf("%d", ans);
}