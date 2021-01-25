#include <unordered_map>
#include <iostream>
#include <utility>
#include <cstring>
#include <cstdlib>
#include <vector>

const int MAX_N = 5e2 + 10;

std::unordered_map<int, int> discretization;
std::vector<int> graph[MAX_N];

bool is_cut_point[MAX_N];
int dfn[MAX_N];
int low[MAX_N];
int time_stamp;

int cut_point_num;
int group_index;
int node_num;
int vis[MAX_N];

int n, m;

void init()
{
    discretization.clear();
    for (int i = 0; i < MAX_N; i++)
        graph[i].clear();

    std::memset(is_cut_point, 0, sizeof(is_cut_point));
    std::memset(dfn, 0, sizeof(dfn));
    std::memset(low, 0, sizeof(low));
    time_stamp = 0;

    group_index = 0;
    std::memset(vis, 0, sizeof(vis));

    n = 0;
}

int build_graph()
{
    std::cin >> m;
    if (m == 0)
        std::exit(0);

    int node_index = 0;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;

        if (discretization.find(u) == discretization.end())
            discretization[u] = node_index++;
        u = discretization[u];

        if (discretization.find(v) == discretization.end())
            discretization[v] = node_index++;
        v = discretization[v];

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    return node_index;
}

void tarjan_dfs(int u, int fa)
{
    time_stamp++;
    dfn[u] = time_stamp;
    low[u] = time_stamp;

    int child = 0;
    for (auto v : graph[u])
    {
        if (v == fa)
            continue;

        if (dfn[v] == 0)
        {
            child++;

            tarjan_dfs(v, u);
            low[u] = std::min(low[u], low[v]);

            if (dfn[u] <= low[v])
                is_cut_point[u] = true;
        }
        else
            low[u] = std::min(low[u], dfn[v]);
    }

    if (fa == -1 and child == 1)
        is_cut_point[u] = false;
}

void tarjan()
{
    for (int i = 0; i < n; i++)
        if (not dfn[i])
            tarjan_dfs(i, -1);
}

void dfs(int u)
{
    vis[u] = group_index;
    node_num++;

    for (auto v : graph[u])
    {
        if (is_cut_point[v] and vis[v] != group_index)
        {
            vis[v] = group_index;
            cut_point_num++;
        }

        if (vis[v] == 0)
            dfs(v);
    }
}

std::pair<long long int, long long int> scan()
{
    std::pair<int, long long int> solution = {0, 1};

    for (int i = 0; i < n; i++)
    {
        if (vis[i] == 0 and not is_cut_point[i])
        {
            group_index++;
            cut_point_num = 0;
            node_num = 0;

            dfs(i);

            if (cut_point_num == 0)
            {
                solution.first += 2;
                solution.second *= node_num * (node_num - 1) / 2;
            }
            else if (cut_point_num == 1)
            {
                solution.first += 1;
                solution.second *= node_num;
            }
        }
    }

    return solution;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    m = -1;
    int t = 0;

    while (m != 0)
    {
        init();

        n = build_graph();
        tarjan();

        auto ans = scan();
        std::cout << "Case " << ++t << ": " << ans.first << " " << ans.second << "\n";
    }
    return 0;
}