#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

template <typename T>
void read(T &x)
{
    T f = 1;
    x = 0;
    char s = getchar();
    while (s < '0' || s > '9')
    {
        if (s == '-')
            f = -1;
        s = getchar();
    }
    while (s >= '0' && s <= '9')
    {
        x = (x << 3) + (x << 1) + (s ^ '0');
        s = getchar();
    }
    x *= f;
}

template <typename T>
void write(T x, char s = '\n')
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (!x)
    {
        putchar('0');
        putchar(s);
        return;
    }
    int tmp[22] = {}, t = 0;
    while (x)
        tmp[t++] = x % 10, x /= 10;
    while (t-- > 0)
        putchar(tmp[t] + '0');
    putchar(s);
}

const int MAXN = 1e5 + 5;

int head[MAXN], to[MAXN << 1], nxt[MAXN << 1], ecnt;
void add(int u, int v)
{
    nxt[++ecnt] = head[u];
    head[u] = ecnt;
    to[ecnt] = v;
}

int n, x, dep[MAXN], cnt, deg[MAXN], c[500], val[500], us[500], bl[MAXN];
pair<int, int> siz[MAXN];
int md;
char ans[MAXN];
vector<int> nod[MAXN];
bool cmp(int x, int y) { return deg[x] > deg[y]; }

void pre(int x, int fa)
{
    dep[x] = dep[fa] + 1;
    nod[dep[x]].push_back(x);
    md = max(md, dep[x]);
    siz[dep[x]].first++;
    siz[dep[x]].second = dep[x];
    for (int i = head[x]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa)
            continue;
        pre(v, x);
    }
}

int f[480][MAXN];

int main()
{
    read(n), read(x);
    for (int i = 2; i <= n; ++i)
    {
        int p;
        read(p);
        add(p, i);
        deg[p]++, deg[i]++;
    }
    pre(1, 0);
    sort(siz + 1, siz + 1 + md);
    for (int i = 1; i <= md; ++i)
    {
        if (siz[i].first != siz[i - 1].first)
            c[++cnt] = 1, val[cnt] = siz[i].first;
        else
            c[cnt]++;
        bl[siz[i].second] = cnt;
    }
    for (int i = 1; i <= n; ++i)
        f[1][i] = -1;
    for (int j = 1; j <= c[1]; ++j)
        f[1][j * val[1]] = 0;
    for (int i = 2; i <= cnt; ++i)
    {
        f[i][0] = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (f[(i - 1)][j] != -1)
                f[i][j] = j;
            else if (j >= val[i] && f[i][j - val[i]] != -1 && (j - f[i][j - val[i]]) / val[i] <= c[i])
                f[i][j] = f[i][j - val[i]];
            else
                f[i][j] = -1;
        }
    }
    if (f[cnt][x] != -1)
        printf("%d\n", md);
    else
        printf("%d\n", md + 1);
    return 0;
}
