#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>

const int INF = 0x7fffffff;
const int MAX_N = 1e3;

std::vector<int> g[MAX_N];
bool inque[MAX_N];
int dis[MAX_N];

inline void spfa(int s)
{
    for (int i = 0; i < MAX_N; i++)
        dis[i] = INF;

    std::queue<int> q;
    dis[s] = 0;
    q.push(s);
    inque[s] = true;

    while (not q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto v : g[u])
        {
            if (dis[v] > dis[u] + 1)
            {
                dis[v] = dis[u] + 1;

                if (not inque[v])
                {
                    q.push(v);
                    inque[v] = true;
                }
            }
        }
    }
}

int main()
{
    int n, x, y;
    std::cin >> n >> x >> y;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            bool tmp;
            std::cin >> tmp;

            if (tmp)
                g[i].push_back(j);
        }
    }

    spfa(x);

    std::cout << dis[y] - 1;
    return 0;
}