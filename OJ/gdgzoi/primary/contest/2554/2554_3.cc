#include <algorithm>
#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
#include <tuple>
#include <queue>
#include <cmath>

const int MAX_N = 5e4 + 10;

std::vector<std::tuple<int, int, int>> input;
std::vector<std::pair<int, double>> g[MAX_N];

int city[MAX_N];
int x[MAX_N];
int s, t;

double min[MAX_N];
double max[MAX_N];
int pre[MAX_N];

std::pair<double, double> EK_bfs()
{
    std::memset(min, 127, sizeof(min));
    for (int i = 0; i < MAX_N; i++)
    {
        max[i] = -1;
        pre[i] = -1;
    }

    std::queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        const int u = q.front();
        q.pop();

        for (auto v : g[u])
        {
            if (pre[v.first] == -1 && v.second > 0)
            {
                min[v.first] = std::min(min[u], v.second);
                max[v.first] = std::max(max[u], v.second);
                pre[v.first] = u;
                q.push(v.first);
            }
        }
    }

    if (pre[t] == -1)
        return std::make_pair<double, double>(-1, -1);
    return std::make_pair(min[t], max[t]);
}

std::pair<double, double> EK()
{
    std::pair<double, double> ans{-1, -1};

    while (true)
    {
        const auto res = EK_bfs();
        if (res.first == -1)
            break;
        if (res.first > ans.first || (res.first == ans.first && res.second < ans.second))
            ans = res;

        int u = t;
        while (u != s)
        {
            for (auto &v : g[pre[u]])
            {
                if (v.first == u)
                {
                    v.second -= res.first;
                    break;
                }
            }

            bool flag = true;
            for (auto &v : g[u])
            {
                if (v.first == pre[u])
                {
                    v.second += res.first;
                    flag = false;
                    break;
                }
            }

            if (flag)
                g[u].emplace_back(std::make_pair(pre[u], res.first));
            u = pre[u];
        }
    }

    return ans;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    for (int _i = 0; _i < m; _i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        input.emplace_back(std::make_tuple(u, v, w));
    }

    for (int i = 0; i < n; i++)
    {
        int t;
        std::cin >> t;

        for (int j = 0; j < t; j++)
        {
            int ct;
            std::cin >> ct;
            city[ct] = i;
        }
    }

    for (int i = 0; i < n; i++)
        std::cin >> x[i];
    std::cin >> s >> t;

    for (auto line : input)
    {
        int u, v;
        double w;
        u = std::get<0>(line);
        v = std::get<1>(line);
        w = std::get<2>(line);

        if (city[u] == city[v])
            w = (w * x[city[u]]) / 100;
        else
            w = (w * (x[city[u]] + x[city[v]])) / 200;

        g[u].emplace_back(std::make_pair(v, w));
        g[v].emplace_back(std::make_pair(u, w));
    }

    const auto ans = EK();
    std::cout << std::floor(ans.first) << " " << std::ceil(ans.second);
    return 0;
}