#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

const int MAX_N = 2e4 + 10;

std::vector<int> g[MAX_N];
std::stack<int> s;

int time_stamp = 0;
int color_cnt = 0;
int color[MAX_N];
int dfn[MAX_N];
int low[MAX_N];

void tarjan(int u)
{
    dfn[u] = low[u] = ++time_stamp;
    s.push(u);

    for (auto v : g[u])
    {
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if (color[v] == 0)
            low[u] = std::min(low[u], dfn[v]);
    }

    if (low[u] == dfn[u])
    {
        ++color_cnt;
        int v = -1;

        do
        {
            v = s.top();
            s.pop();
            color[v] = color_cnt;
        } while (v != u);
    }
}

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        int m;
        std::cin >> m;

        for (int j = 0; j < m; j++)
        {
            int v;
            std::cin >> v;
            g[i].push_back(n + v);
        }
    }

    for (int i = 0; i < n; i++)
    {
        int v;
        std::cin >> v;
        g[v + n].push_back(i);
    }

    for (int i = 0; i < n; i++)
        if (!dfn[i])
            tarjan(i);

    for (int i = 0; i < n; i++)
    {
        std::vector<int> ans;
        for (auto v : g[i])
            if (color[v] == color[i])
                ans.push_back(v);
        std::sort(ans.begin(), ans.end());

        std::cout << ans.size() << " ";
        for (auto i : ans)
            std::cout << i - n << " ";
        std::cout << "\n";
    }
    return 0;
}
