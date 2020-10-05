#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>

struct data
{
    int v;
    int w;
};

const int INF = 0x7fffffff;
const int MAXN = 1e4;
const int S = 0;
std::vector<data> g[MAXN];
bool inque[MAXN];
int vis[MAXN];
int dis[MAXN];
int n, m, k;

inline void init()
{
    std::memset(inque, false, sizeof(inque));
    std::memset(vis, 0, sizeof(vis));

    for (int i = 1; i <= n + m; i++)
    {
        dis[i] = INF;
        g[i].clear();
        g[S].push_back((data){i, 0});
    }
}

inline bool SLF_SPFA()
{
    std::deque<int> dq;
    dq.push_back(S);
    inque[S] = true;
    vis[S] = 1;

    while (!dq.empty())
    {
        int u = dq.front();
        dq.pop_front();
        inque[u] = false;

        for (auto i : g[u])
        {
            int v = i.v;
            int w = i.w;

            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;

                if (vis[v] >= n + m)
                    return false;
                if (!inque[v])
                {
                    vis[v]++;
                    inque[v] = true;

                    if (dq.empty() || dis[v] > dis[dq.front()])
                        dq.push_back(v);
                    else
                        dq.push_front(v);
                }
            }
        }
    }

    return true;
}

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> n >> m >> k;

        init();

        for (int i = 0; i < k; i++)
        {
            int x, y, c;
            std::cin >> x >> y >> c;
            g[x].push_back((data){y + n, c});
            g[y + n].push_back((data){x, -c});
        }

        std::cout << (SLF_SPFA() ? "Yes" : "No") << "\n";
    }
    return 0;
}