#include <cstddef>
#include <iostream>
#include <cstring>
#include <climits>
#include <vector>
#include <queue>

struct node
{
    int v;
    long long w;
};

const int MAX_N = 5e4 + 10;
const int MAX_K = 1e2 + 10;
const long long INF = 9187201950435737471;

std::vector<node> g[MAX_N];
std::vector<int> mark;
int read_mark[MAX_K];
int n, m, k, s, t;

bool inque[MAX_N];
long long dis[MAX_K][MAX_N];

void SPFA(int start, int id)
{
    std::memset(dis[id], 127, sizeof(dis[id]));
    std::memset(inque, false, sizeof(inque));

    std::queue<int> q;
    q.push(start);
    inque[start] = true;
    dis[id][start] = 0;

    while (!q.empty())
    {
        const int u = q.front();
        q.pop();
        inque[u] = false;

        for (auto v : g[u])
        {
            if (dis[id][v.v] > dis[id][u] + v.w)
            {
                dis[id][v.v] = dis[id][u] + v.w;

                if (!inque[v.v])
                {
                    q.push(v.v);
                    inque[v.v] = true;
                }
            }
        }
    }
}

long long min_dis = INF;
bool vis[MAX_K];

void dfs(int u, long long d, int num)
{
    if (num == k)
    {
        min_dis = std::min(min_dis, d + dis[u][t]);
        return;
    }

    for (int i = 0; i < k; i++)
    {
        if (!vis[i] && dis[u][mark[i]] != INF)
        {
            vis[i] = true;
            dfs(i, d + dis[u][mark[i]], num + 1);
            vis[i] = false;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m >> k >> s >> t;

    for (int _i = 0; _i < m; _i++)
    {
        int u, v;
        long long w;
        std::cin >> u >> v >> w;

        g[u].push_back({v, w});
    }

    for (int i = 0; i < k; i++)
        std::cin >> read_mark[i];
    for (int i = 0; i < k; i++)
        if (read_mark[i] != s && read_mark[i] != t)
            mark.push_back(read_mark[i]);

    k = mark.size();
    mark.push_back(s);
    mark.push_back(t);

    for (int i = 0; i < k + 2; i++)
        SPFA(mark[i], i);

    if (k == 0)
    {
        if (dis[k][t] == INF)
            std::cout << "-1";
        else
            std::cout << dis[k][t];
    }
    else
    {
        dfs(k, 0, 0);
        if (min_dis == INF)
            std::cout << "-1";
        else
            std::cout << min_dis;
    }

    return 0;
}