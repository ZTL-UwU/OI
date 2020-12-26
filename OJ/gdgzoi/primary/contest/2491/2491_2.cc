#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>
#include <deque>
#include <map>

const int INF = 0x7fffffff;
const int MAX_N = 3e5;

// pair(x, y)
// vector(x_sorted_index, y_sorted_index, unsorted_index)
std::map<std::pair<int, int>, std::vector<int>> cord_pos;

// pair(x, y)
std::map<std::pair<int, int>, bool> build_inque;
std::map<std::pair<int, int>, bool> build_vis;
std::pair<int, int> x_sorted[MAX_N];
std::pair<int, int> y_sorted[MAX_N];

// pair(v, w)
std::vector<std::pair<int, int>> g[MAX_N];

bool SPFA_inque[MAX_N];
int dis[MAX_N];

int n;

inline int SPFA(int start, int end)
{
    for (int i = 0; i < MAX_N; i++)
        dis[i] = INF;

    std::deque<int> dq;
    dq.push_front(start);
    SPFA_inque[start] = true;
    dis[start] = 0;

    while (not dq.empty())
    {
        int u = dq.front();
        dq.pop_front();
        SPFA_inque[u] = false;

        for (auto v : g[u])
        {
            if (dis[u] + v.second < dis[v.first])
            {
                dis[v.first] = dis[u] + v.second;

                if (not SPFA_inque[v.first])
                {
                    SPFA_inque[dis[v.first]] = true;

                    if (dq.empty() or dis[v.first] > dis[dq.front()])
                        dq.push_back(v.first);
                    else
                        dq.push_front(v.first);
                }
            }
        }
    }

    return dis[end];
}

inline void build_g(std::pair<int, int> start, std::pair<int, int> end)
{
    std::queue<std::pair<int, int>> q;
    q.push(start);
    build_vis[start] = true;

    while (!q.empty())
    {
        std::pair<int, int> u;
        u = q.front();
        q.pop();

        if (u == end)
            break;

        std::vector<std::pair<int, int>> v;
        if (cord_pos[u][0] - 1 >= 0)
            v.push_back(x_sorted[cord_pos[u][0] - 1]);
        if (cord_pos[u][0] + 1 < n)
            v.push_back(x_sorted[cord_pos[u][0] + 1]);

        if (cord_pos[u][1] - 1 >= 0)
            v.push_back(y_sorted[cord_pos[u][1] - 1]);
        if (cord_pos[u][1] + 1 < n)
            v.push_back(y_sorted[cord_pos[u][1] + 1]);

        for (auto i : v)
        {
            g[cord_pos[u][2]].push_back(std::pair<int, int>(
                cord_pos[i][2], std::min(std::abs(u.first - i.first), std::abs(u.second - i.second))));

            if (not build_vis[i])
            {
                build_vis[i] = true;
                q.push(i);
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n;

    std::pair<int, int> P1;
    std::pair<int, int> Pn;

    for (int i = 0; i < n; i++)
    {
        int x, y;
        std::cin >> x >> y;
        std::pair<int, int> cord = std::pair<int, int>(x, y);

        if (i == 0)
            P1 = cord;
        if (i == n - 1)
            Pn = cord;

        x_sorted[i] = cord;
        y_sorted[i] = cord;

        cord_pos[cord].resize(3);
        cord_pos[cord][2] = i;
    }

    std::sort(x_sorted, x_sorted + n, [](std::pair<int, int> a, std::pair<int, int> b) { return a.first < b.first; });
    std::sort(y_sorted, y_sorted + n, [](std::pair<int, int> a, std::pair<int, int> b) { return a.second < b.second; });

    for (int i = 0; i < n; i++)
    {
        cord_pos[x_sorted[i]][0] = i;
        cord_pos[y_sorted[i]][1] = i;
    }

    build_g(P1, Pn);

    std::cout << SPFA(0, n - 1);
    return 0;
}