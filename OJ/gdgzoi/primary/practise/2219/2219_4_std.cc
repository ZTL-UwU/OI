#include <iostream>
#include <cstring>
#include <queue>

#define SIZE 210
#define INF 1e+09

using namespace std;

struct edge
{
    int to, cap, reverse;
};

vector<edge> graph[SIZE];
int cur[SIZE], depth[SIZE], a[SIZE][SIZE], sink = 200;

bool bfs(void)
{
    queue<int> q;
    int u, i, v;

    memset(depth, -1, sizeof(depth));
    q.push(0);
    depth[0] = 0;
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        if (u == sink)
        {
            return true;
        }
        for (i = 0; i < graph[u].size(); ++i)
        {
            v = graph[u][i].to;
            if ((depth[v] == -1) && (graph[u][i].cap > 0))
            {
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }
    }

    return false;
}

int dfs(int u, int flow)
{
    int i, v, ret = 0, delta;

    if ((!flow) || (u == sink))
    {
        return flow;
    }
    for (i = cur[u]; i < graph[u].size(); ++i)
    {
        cur[u] = i;
        edge &temp = graph[u][i];
        v = temp.to;
        if ((depth[v] == depth[u] + 1) && (temp.cap > 0))
        {
            delta = dfs(v, min(flow - ret, temp.cap));
            if (delta > 0)
            {
                ret += delta;
                temp.cap -= delta;
                graph[v][temp.reverse].cap += delta;
                if (ret == flow)
                {
                    return ret;
                }
            }
        }
    }

    return ret;
}

int dinic(void)
{
    int ret = 0, delta;

    while (bfs())
    {
        memset(cur, 0, sizeof(cur));
        delta = dfs(0, INF);
        if (!delta)
        {
            return ret;
        }
        ret += delta;
    }

    return ret;
}

void addedge(int u, int v, int cap)
{
    graph[u].push_back({v, cap, graph[v].size()});
    graph[v].push_back({u, 0, graph[u].size() - 1});

    return;
}

int main(int argc, char **argv)
{
    int n, a1, a2, an, b1, b2, bn, i, j;
    char c;

    while (~scanf("%d%d%d%d%d%d%d", &n, &a1, &a2, &an, &b1, &b2, &bn))
    {
        ++a1;
        ++a2;
        ++b1;
        ++b2;
        memset(a, 0, sizeof(a));
        for (i = 0; i < SIZE; ++i)
        {
            graph[i].clear();
        }
        for (i = 1; i <= n; ++i)
        {
            for (j = 1; j <= n; ++j) // 建图
            {
                cin >> c;
                if (c == 'O')
                {
                    a[i][j] = 1;
                    addedge(i, j, 1);
                }
                else if (c == 'N')
                {
                    a[i][j] = 2;
                    addedge(i, j, INF);
                }
            }
        }
        addedge(0, a1, an);
        addedge(a2, sink, an);
        addedge(0, b1, bn);
        addedge(b2, sink, bn);
        if (dinic() != an + bn) // A这边要Dinic一次
        {
            printf("No\n");
            continue;
        }
        for (i = 0; i < SIZE; ++i)
        {
            graph[i].clear();
        }
        for (i = 1; i <= n; ++i)
        {
            for (j = 1; j <= n; ++j)
            {
                if (a[i][j] == 1)
                {
                    addedge(i, j, 1);
                }
                else if (a[i][j] == 2)
                {
                    addedge(i, j, INF);
                }
            }
        }
        addedge(0, a2, an);
        addedge(a1, sink, an);
        addedge(0, b2, bn);
        addedge(b1, sink, bn);
        if (dinic() == an + bn) // B这边也要Dinic一次
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }

    return 0;
}