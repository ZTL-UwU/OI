#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

const long long INF = 1e18 + 5;
const int MAX_N = 55;
const int MAX_W = 20005;

struct node
{
    int x;
    int w;
    node(int a, int b)
    {
        x = a;
        w = b;
    }
};

int mod;
int n, m;

vector<node> G[MAX_N];
long long t;
long long d[MAX_N][MAX_W];

struct point
{
    int x, l;
    point(int a, int y)
    {
        x = a;
        l = y;
    }
};

bool inq[MAX_N][MAX_W];
void the_dead_algorithm_since_2019()
{
    queue<point> q;

    for (int i = 0; i <= n; ++i)
        for (int j = 0; j < MAX_W; ++j)
            d[i][j] = INF;

    q.push({1, 0});
    d[1][0] = 0;

    while (q.size())
    {
        point x = q.front();
        q.pop();

        inq[x.x][x.l] = false;

        for (int i = 0; i < G[x.x].size(); ++i)
        {
            int y = G[x.x][i].x;
            int w = G[x.x][i].w;
            int z = (x.l + w) % mod;
            if (d[y][z] > d[x.x][x.l] + w)
            {
                d[y][z] = d[x.x][x.l] + w;

                if (!inq[y][z])
                {
                    inq[y][z] = true;
                    q.push({y, z});
                }
            }
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int _ = 0; _ < T; ++_)
    {
        scanf("%d %d %lld", &n, &m, &t);

        for (int i = 0; i <= n; ++i)
            G[i].clear();
        mod = 1e9;

        for (int i = 1; i <= m; i++)
        {
            int x, y, w;
            scanf("%d %d %d", &x, &y, &w);
            x += 1;
            y += 1;

            if (x == 1 || y == 1)
                mod = min(mod, 2 * w);

            if (x == 1 && y == 1)
                mod = min(mod, w);

            G[x].push_back({y, w});
            G[y].push_back({x, w});
        }

        if (mod == 1e9)
        {
            printf("Impossible\n");
            continue;
        }

        the_dead_algorithm_since_2019();

        if (d[n][t % mod] <= t)
            printf("Possible\n");
        else
            printf("Impossible\n");
    }
    return 0;
}