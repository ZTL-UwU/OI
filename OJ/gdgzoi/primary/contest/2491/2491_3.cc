#include <iostream>
#include <vector>

const int MAX_N = 2e5;

std::vector<int> g[MAX_N];

bool is_cut_point[MAX_N];
int size[MAX_N];
int dfn[MAX_N];
int low[MAX_N];
int time_stamp;

long long int ans[MAX_N];
int n, m;

inline void tarjan(int u, int fa)
{
    time_stamp++;
    dfn[u] = time_stamp;
    low[u] = time_stamp;
    size[u] = 1;

    int child = 0;
    int size_sum = 0;
    for (auto v : g[u])
    {
        if (v == fa)
            continue;

        if (dfn[v] == 0)
        {
            tarjan(v, u);
            size[u] += size[v];
            low[u] = std::min(low[u], low[v]);

            if (low[v] >= dfn[u])
            {
                ans[u] += (long long int)size[v] * (n - size[v]);
                size_sum += size[v];
                child++;

                if (fa != -1 or child > 1)
                    is_cut_point[u] = true;
            }
        }
        else
            low[u] = std::min(low[u], dfn[v]);
    }

    if (not is_cut_point[u])
        ans[u] = (long long int)2 * (n - 1);
    else
        ans[u] += (long long int)(n - size_sum - 1) * (size_sum + 1) + n - 1;
}

int main()
{
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
        if (not dfn[i])
            tarjan(i, 0);

    for (int i = 1; i <= n; i++)
        std::cout << ans[i] << "\n";
    return 0;
}