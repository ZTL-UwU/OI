#include <iostream>
#include <cstring>
#include <queue>

#define SIZE 65000
#define INF 1e+09

using namespace std;

struct edge
{
    int to, cap, cost, reverse;
};

vector<edge> graph[SIZE];
int pre[SIZE], dis[SIZE], edgeindex[SIZE], sink, _cost[6][SIZE];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
bool inqueue[SIZE];

bool spfa(int s)
{
    queue<int> q;
    int u, v, i;

    memset(pre, -1, sizeof(pre));
    for (i = 0; i < SIZE; ++i)
    {
        dis[i] = INF;
    }
    memset(edgeindex, -1, sizeof(edgeindex));
    memset(inqueue, false, sizeof(inqueue));
    dis[s] = 0;
    q.push(s);
    inqueue[s] = true;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        inqueue[u] = false;
        for (i = 0; i < graph[u].size(); ++i)
        {
            v = graph[u][i].to;
            if ((graph[u][i].cap > 0) && (dis[v] > dis[u] + graph[u][i].cost))
            {
                dis[v] = dis[u] + graph[u][i].cost;
                pre[v] = u;
                edgeindex[v] = i;
                if (!inqueue[v])
                {
                    q.push(v);
                    inqueue[v] = true;
                }
            }
        }
    }

    return (dis[sink] != INF);
}

int mincostmaxflow(int s) // 求最小费用最大流
{
    int u, v, maxflow = 0, delta, mincost = 0, i;

    while (spfa(s))
    {
        delta = INF;
        for (v = sink; v != s; v = u)
        {
            u = pre[v];
            i = edgeindex[v];
            delta = min(delta, graph[u][i].cap);
        }
        for (v = sink; v != s; v = u)
        {
            u = pre[v];
            i = edgeindex[v];
            mincost += delta * graph[u][i].cost;
            graph[u][i].cap -= delta;
            graph[v][graph[u][i].reverse].cap += delta;
        }
        maxflow += delta;
    }

    return mincost;
}

void addedge(int u, int v, int cap, int cost)
{
    graph[u].push_back({v, cap, cost, graph[v].size()});
    graph[v].push_back({u, 0, -cost, graph[u].size() - 1});

    return;
}

int main(int argc, char **argv)
{
    freopen("a.out", "r", stdin);
    int n, u, v, i, j, k, r, c, temp;
    char ch;

    scanf("%d", &n);
    temp = n * 5;
    sink = n * 10 + 1;
    for (i = 1; i <= 5; ++i) // 以下建图
    {
        addedge(i * n, sink, 1, 0); // 连终点
        for (j = 1; j <= n; ++j)
        {
            addedge((i - 1) * n + j, temp + (i - 1) * n + j, 1, 0); // 拆点容量限制,即一个格子只能走一个人
            cin >> ch;
            if (ch == '@')
            {
                addedge(0, (i - 1) * n + 1, 1, 0); // 连起点
            }
            else
            {
                _cost[i][j] = ch - '0';
            }
        }
    }
    for (i = 1; i <= 5; ++i)
    {
        for (j = 1; j <= n; ++j)
        {
            for (k = 0; k < 4; ++k)
            {
                r = i + dx[k];
                c = j + dy[k];
                if (((!r) || (r > 5)) || ((!c) || (c > n)))
                {
                    continue;
                }
                addedge(temp + (i - 1) * n + j, (r - 1) * n + c, 1, _cost[r][c]); // 连边
            }
        }
    }

    printf("%d", mincostmaxflow(0));

    return 0;
}