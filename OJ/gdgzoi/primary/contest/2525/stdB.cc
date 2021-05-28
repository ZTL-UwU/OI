#include <cstdio>
using namespace std;

const int maxn = 1000;

int s[maxn], st[maxn];

void rev(int k)
{
    if (st[k])
    {
        st[k] = 0;
    }
    else
    {
        st[k] = 1;
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", st + i);
    }

    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", s + i);
    }

    for (int i = 1; i <= m; ++i)
    {
        int e;
        scanf("%d", &e);
        if (e == 1)
        {
            int x;
            scanf("%d", &x);
            rev(x);
        }
        else if (e == 2)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            for (int i = x; i <= y; ++i)
            {
                rev(i);
            }
        }
        else if (e == 3)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            int res = 0;
            for (int i = x; i <= y; ++i)
            {
                if (st[i])
                {
                    res += s[i];
                }
            }

            printf("%d\n", res);
        }
    }
    return 0;
}