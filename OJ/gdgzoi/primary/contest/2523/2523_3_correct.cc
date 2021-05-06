#include <cstring>
#include <iostream>
#include <vector>
#include <queue>

const int INF = 0x7fffffff;
const int MAX_W = 2e4 + 10;
const int MAX_N = 1e2;
const int S = 0;

struct node
{
    int v, w;
};

struct queue_data
{
    int u, l;
};

long long int dis[MAX_N][MAX_W];
std::vector<node> g[MAX_N];
bool inque[MAX_N][MAX_W];
int mod = INF;

void init(int n)
{
    mod = INF;
    std::memset(inque, false, sizeof(inque));
    std::memset(dis, 0x7f, sizeof(dis));
    for (int i = 0; i <= n; i++)
        g[i].clear();
}

void SPFA()
{
    std::queue<queue_data> q;
    q.push({S, 0});
    inque[S][0] = true;
    dis[S][0] = 0;

    while (!q.empty())
    {
        const auto u = q.front();
        q.pop();
        inque[u.u][u.l] = false;

        for (auto v : g[u.u])
        {
            const int z = (u.l + v.w) % mod;
            if (dis[v.v][z] > dis[u.u][u.l] + v.w)
            {
                dis[v.v][z] = dis[u.u][u.l] + v.w;

                if (!inque[v.v][z])
                {
                    q.push({v.v, z});
                    inque[v.v][z] = true;
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

    int T;
    std::cin >> T;

    for (int _i = 0; _i < T; _i++)
    {
        int n, m;
        long long int t;
        std::cin >> n >> m >> t;
        init(n);

        for (int __i = 0; __i < m; __i++)
        {
            int u, v, w;
            std::cin >> u >> v >> w;

            if (u == S || v == S)
                mod = std::min(mod, w * 2);
            if (u == S && v == S)
                mod = std::min(mod, w);

            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        if (mod == INF)
            std::cout << "Impossible\n";
        else
        {
            SPFA();

            if (dis[n - 1][t % mod] <= t)
                std::cout << "Possible\n";
            else
                std::cout << "Impossible\n";
        }
    }
    return 0;
}
