#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

const int MAX_N = 4e4;

std::vector<int> g[MAX_N];
int indegree[MAX_N];

inline void init()
{
    for (int i = 0; i < MAX_N; i++)
        g[i].clear();

    std::memset(indegree, 0, sizeof(indegree));
}

std::vector<int> topology_sort(int n)
{
    std::vector<int> res;
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;

    for (int i = 1; i <= n; i++)
        if (indegree[i] == 0)
            q.push(i);

    while (!q.empty())
    {
        int u = q.top();
        q.pop();
        res.push_back(u);

        for (auto v : g[u])
        {
            indegree[v]--;

            if (indegree[v] == 0)
                q.push(v);
        }
    }

    return res;
}

int main()
{
    int T;
    std::cin >> T;

    for (int t = 0; t < T; t++)
    {
        init();

        int n, m;
        std::cin >> n >> m;

        for (int i = 0; i < m; i++)
        {
            int u, v;
            std::cin >> u >> v;

            g[u].push_back(v);
            indegree[v]++;
        }

        for (auto i : topology_sort(n))
            std::cout << i << " ";
        std::cout << "\n";
    }
    return 0;
}