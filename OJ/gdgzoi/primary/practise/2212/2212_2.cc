#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

struct data
{
    int v;
    int w;
};

const int MAXN = 1e5;
const int SUPER_ROOT = 0;
const int INF = 0x7fffffff;

std::vector<data> g[MAXN];
bool inque[MAXN];
int cnt[MAXN];
int dis[MAXN];
int n, m;

inline bool spfa(int start)
{
    for (int i = 0; i < MAXN; i++)
        dis[i] = -1;

    std::queue<int> q;
    q.push(start);
    inque[start] = true;
    dis[start] = 0;
    cnt[start] = 1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inque[u] = false;

        for (auto v : g[u])
        {
            if (dis[v.v] < dis[u] + v.w)
            {
                dis[v.v] = dis[u] + v.w;
                if (!inque[v.v])
                {
                    cnt[v.v]++;
                    inque[v.v] = true;
                    q.push(v.v);

                    if (cnt[v.v] > n + 1)
                        return false;
                }
            }
        }
    }

    return true;
}

int main()
{
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, a, b;
        std::cin >> u >> v >> a >> b;
        u++;
        v++;
        g[v].push_back((data){u, -a});
        g[u].push_back((data){v, -b});
    }

    for (int i = 1; i <= n; i++)
        g[SUPER_ROOT].push_back((data){i, 0});

    if (!spfa(SUPER_ROOT))
    {
        std::cout << "-1";
        return 0;
    }

    for (int i = 1; i <= n; i++)
        std::cout << dis[i] << " ";
    return 0;
}