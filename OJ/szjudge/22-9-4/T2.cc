#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

const int MAX_N = 5e5 + 10;

struct gedge
{
    int v, eno;
};

struct edge
{
    int no, u, v;
};

bool cmp(edge e1, edge e2) { return e1.no < e2.no; }

std::priority_queue<int, std::vector<int>, std::greater<int>> q;
std::vector<gedge> g[MAX_N];
std::vector<edge> e1;
std::vector<edge> e2;

int val[MAX_N];
bool c1[MAX_N];

int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, c;
        std::cin >> u >> v >> c;

        if (c == 1)
            e1.push_back({i, u, v});
        else
        {
            e2.push_back({i, u, v});
            g[u].push_back((gedge){v, i});
            g[v].push_back((gedge){u, i});
        }
    }

    std::sort(e1.begin(), e1.end(), cmp);

    int num = 0;
    for (auto e : e1)
    {
        if (!c1[e.u] && !c1[e.v])
        {
            c1[e.u] = true;
            c1[e.v] = true;
        }

        if (c1[e.u])
        {
            c1[e.v] = true;
            for (auto v : g[e.v])
                if (c1[v.v])
                    q.push(v.eno);
        }
        if (c1[e.v])
        {
            c1[e.u] = true;
            for (auto v : g[e.u])
                if (c1[v.v])
                    q.push(v.eno);
        }

        val[e.no] = ++num;

        while (!q.empty() && q.top() < e.no)
        {
            val[q.top()] = ++num;
            q.pop();
        }
    }

    for (int i = 0; i < m; i++)
        std::cout << val[i] << " ";
    return 0;
}