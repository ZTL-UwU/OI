#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int maxn = 200005;

struct edge
{
    int x;
    int y;
};

struct query
{
    int t, x, ans;
};

vector<int> G[maxn];
int F[maxn][25];
int depth[maxn];
int lgx[maxn];
edge E[maxn];
query Q[maxn];
int S[maxn], dis[maxn], d[2][maxn];
bool mark[maxn];

void dfs(int x, int f)
{
    depth[x] = depth[f] + 1;

    F[x][0] = f;
    for (int i = 1; (1 << i) < depth[x]; ++i)
        F[x][i] = F[F[x][i - 1]][i - 1];

    for (int y : G[x])
    {
        if (y == f)
            continue;

        dfs(y, x);
    }
}

int LCA(int x, int y)
{
    if (depth[x] < depth[y])
        swap(x, y);

    while (depth[x] > depth[y])
        x = F[x][lgx[depth[x] - depth[y]]];

    if (x == y)
        return x;

    for (int i = lgx[depth[x] - 1]; i >= 0; i--)
    {
        if (F[x][i] != F[y][i] && (1 << i) < depth[x])
        {
            x = F[x][i];
            y = F[y][i];
        }
    }
    return F[x][0];
}

int calc(int x, int y) { return depth[x] + depth[y] - depth[LCA(x, y)] * 2; }

void init(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        S[i] = i;
        d[0][i] = i;
        d[1][i] = i;
    }
}

int getf(int x)
{
    if (S[x] == x)
        return x;

    return S[x] = getf(S[x]);
}

void merge(int x, int y)
{
    int a = getf(x);
    int b = getf(y);
    S[a] = b;

    int mxd = dis[a], maxd0 = d[0][a], maxd1 = d[1][a];
    if (mxd < dis[b])
    {
        mxd = dis[b];
        maxd0 = d[0][b];
        maxd1 = d[1][b];
    }

    static const int d1[] = {0, 0, 1, 1}, d2[] = {0, 1, 0, 1};

    for (int i = 0; i < 4; ++i)
    {
        int v = calc(d[d1[i]][a], d[d2[i]][b]);
        if (mxd < v)
        {
            mxd = v;
            maxd0 = d[d1[i]][a];
            maxd1 = d[d2[i]][b];
        }
    }

    dis[b] = mxd;
    d[0][b] = maxd0;
    d[1][b] = maxd1;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    init(maxn - 1);
    for (int i = 2; i <= n; i++)
        lgx[i] = lgx[i / 2] + 1;

    for (int i = 1; i < n; ++i)
    {
        scanf("%d %d", &E[i].x, &E[i].y);
        G[E[i].x].push_back(E[i].y);
        G[E[i].y].push_back(E[i].x);
    }
    dfs(1, 0);

    for (int i = 1; i <= m; ++i)
    {
        scanf("%d %d", &Q[i].t, &Q[i].x);
        if (Q[i].t == 1)
            mark[Q[i].x] = true;
    }

    for (int i = 1; i < n; ++i)
        if (!mark[i])
            merge(E[i].x, E[i].y);

    for (int i = m; i >= 1; --i)
    {
        if (Q[i].t == 2)
        {
            int a = getf(Q[i].x);
            Q[i].ans = max({calc(Q[i].x, d[0][a]), calc(Q[i].x, d[1][a]), calc(Q[i].x, a)});
        }
        else
            merge(E[Q[i].x].x, E[Q[i].x].y);
    }

    for (int i = 1; i <= m; ++i)
        if (Q[i].t == 2)
            printf("%d\n", Q[i].ans);

    return 0;
}