#include <algorithm>
#include <bits/c++config.h>
#include <iostream>
#include <vector>

const int MAX_N = 1e5 + 10;

struct Edge
{
    int u;
    int v;
    int w;
};

struct Query
{
    int id;
    int x;
    int w;
    int ans;
};

std::vector<Query> query;
std::vector<Edge> edge;

int sum[MAX_N];
int fa[MAX_N];

int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx == fy)
        return;

    fa[fx] = fy;
    sum[fy] += sum[fx];
}

int main()
{
    std::ios::sync_with_stdio(false);

    int n, m, q;
    std::cin >> n >> m >> q;
    for (int i = 0; i < MAX_N; i++)
    {
        sum[i] = 1;
        fa[i] = i;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        edge.push_back({u, v, w});
    }

    for (int i = 0; i < q; i++)
    {
        int x, w;
        std::cin >> x >> w;
        query.push_back({i, x, w, 0});
    }

    std::sort(edge.begin(), edge.end(), [](Edge e1, Edge e2) -> bool { return e1.w < e2.w; });
    std::sort(query.begin(), query.end(), [](Query q1, Query q2) -> bool { return q1.w < q2.w; });

    std::size_t k = 0;
    for (std::size_t i = 0; i < query.size(); i++)
    {
        for (std::size_t j = k; j < edge.size(); j++)
        {
            if (edge[j].w <= query[i].w)
                merge(edge[j].u, edge[j].v);
            else
            {
                k = j;
                break;
            }
        }

        query[i].ans = sum[find(query[i].x)];
    }

    std::sort(query.begin(), query.end(), [](Query q1, Query q2) -> bool { return q1.id < q2.id; });

    for (const auto q : query)
        std::cout << q.ans << "\n";
    return 0;
}
