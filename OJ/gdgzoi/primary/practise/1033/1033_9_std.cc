#include <iostream>
#include <cstdio>
using namespace std;
const int SIZE = 30005;
int fa[SIZE], d[SIZE], size[SIZE], t; // d记录到父节点距离 size记录子树大小
int get(int x)
{
    if (x == fa[x])
        return x;

    d[x] += d[fa[x]];
    return fa[x] = get(fa[x]);
}

void merge(int x, int y)
{
    x = get(x), y = get(y);
    fa[x] = y;
    d[x] += size[y];
    size[y] += size[x];
    return;
}

int main()
{
    //    freopen("galaxy1.in", "r", stdin);
    cin >> t;
    for (int i = 1; i < SIZE; i++)
    {
        fa[i] = i;
        d[i] = 0;
        size[i] = 1;
    }

    while (t--)
    {
        char f;
        int x, y;
        scanf("\n%c %d %d", &f, &x, &y);
        switch (f)
        {
            case 'M':
                merge(x, y);
                break;
            case 'C':
                if (get(x) != get(y))
                {
                    printf("%d\n", -1);
                    continue;
                }
                int ans = d[x] - d[y];
                ans = ans < 0 ? -ans : ans;
                printf("%d\n", ans - 1);
                break;
        }
    }
    return 0;
}