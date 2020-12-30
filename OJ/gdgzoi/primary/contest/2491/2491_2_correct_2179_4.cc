#include <functional>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>

const int INF = 0x7fffffff;
const int MAX_N = 3e5;
const int VAL = 10;
const int R = 200;

struct pos
{
    int x_cord;
    int y_cord;
    int index;
};

std::vector<std::pair<int, int>> g[MAX_N];
pos cord[MAX_N];
int n;

bool inque[MAX_N];
bool vis[MAX_N];
int dis[MAX_N];
int cnt[MAX_N];

inline int Dijkstra(int start, int end)
{
    for (int i = 0; i < MAX_N; i++)
        dis[i] = INF;
    dis[start] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::pair<int, int>(0, start));

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;

        vis[u] = true;
        for (auto v : g[u])
        {
            if (not vis[v.first] and dis[u] + v.second < dis[v.first])
            {
                dis[v.first] = dis[u] + v.second;
                pq.push(std::pair<int, int>(dis[v.first], v.first));
            }
        }
    }

    return dis[end];
}

inline void add_edge(std::function<bool(pos, pos)> f)
{
    std::sort(cord, cord + n, f);
    for (int i = 0; i < n - 1; i++)
    {
        pos u = cord[i];
        pos v = cord[i + 1];
        int w = std::min(std::abs(u.x_cord - v.x_cord), std::abs(u.y_cord - v.y_cord));

        g[u.index].push_back(std::pair<int, int>(v.index, w));
        g[v.index].push_back(std::pair<int, int>(u.index, w));
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        std::cin >> cord[i].x_cord >> cord[i].y_cord;
        cord[i].index = i;
    }

    add_edge([](pos a, pos b) { return a.x_cord == b.x_cord ? a.y_cord < b.y_cord : a.x_cord < b.x_cord; });
    add_edge([](pos a, pos b) { return a.y_cord == b.y_cord ? a.x_cord < b.x_cord : a.y_cord < b.y_cord; });

    std::cout << Dijkstra(0, n - 1);
    return 0;
}
