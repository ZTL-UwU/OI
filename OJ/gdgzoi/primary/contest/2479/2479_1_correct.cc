#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

const int INF = 0x7fffffff / 2;
const int MAX_N = 6e4;

struct edge
{
    int v;
    int w;
};

std::vector<edge> g[MAX_N];
bool inque[MAX_N];
int old_dis[MAX_N];
int dis[MAX_N];

inline void SPFA(int S)
{
    for (int i = 0; i < MAX_N; i++)
        dis[i] = INF;
    std::queue<int> q;
    q.push(S);
    inque[S] = true;
    dis[S] = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inque[u] = false;

        for (auto v : g[u])
        {
            if (dis[v.v] > dis[u] + v.w)
            {
                dis[v.v] = dis[u] + v.w;
                if (not inque[v.v])
                {
                    inque[v.v] = true;
                    q.push(v.v);
                }
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m, k;
    std::cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        g[u].push_back((edge){v, w});
        g[v].push_back((edge){u, w});
    }

    SPFA(n);

    memcpy(old_dis, dis, sizeof(dis));

    for (int i = 0; i < k; i++)
    {
        int id, w;
        std::cin >> id >> w;
        g[n + 1].push_back((edge){id, old_dis[id] - w});
    }

    SPFA(n + 1);

    for (int i = 1; i <= n - 1; i++)
    {
        if (dis[i] <= old_dis[i])
            std::cout << "1\n";
        else
            std::cout << "0\n";
    }
    return 0;
}