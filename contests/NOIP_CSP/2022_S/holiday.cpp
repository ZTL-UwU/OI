#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>

const int INF = 2147483640;
const int MAX_N = 2520;

std::vector<int> g[MAX_N];
int dis[MAX_N][MAX_N];
unsigned long long a[MAX_N];
bool inque[MAX_N];
int n, m, d;

void SPFA(int start)
{
    std::memset(inque, 0, sizeof(inque));
    for (int i = 1; i <= n; i++)
        dis[i][start] = INF;
    std::queue<int> q;
    q.push(start);
    inque[start] = true;
    dis[start][start] = 0;

    while (!q.empty())
    {
        const int u = q.front();
        q.pop();

        for (int v : g[u])
        {
            if (dis[v][start] > dis[u][start] + 1)
            {
                dis[v][start] = dis[u][start] + 1;

                if (!inque[v])
                {
                    inque[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int main()
{
    std::freopen("holiday.in", "r", stdin);
    std::freopen("holiday.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n >> m >> d;

    for (int i = 2; i <= n; i++)
        std::cin >> a[i];

    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
        SPFA(i);

    unsigned long long ans = 0;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 2; j <= n; j++)
        {
            if (j != i)
            {
                for (int k = 2; k <= n; k++)
                {
                    if (k != i && k != j)
                    {
                        for (int l = 2; l <= n; l++)
                        {
                            if (l != i && l != j && l != k)
                            {
                                if (dis[i][j] - 1 <= d && dis[j][k] - 1 <= d && dis[k][l] - 1 <= d && dis[l][1] - 1 <= d
                                    && dis[1][i] - 1 <= d)
                                {
                                    ans = std::max(ans, a[i] + a[j] + a[k] + a[l]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    std::cout << ans;
    return 0;
}
