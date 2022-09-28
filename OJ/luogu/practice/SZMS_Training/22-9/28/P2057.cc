#include <iostream>
#include <queue>

const int MAX_N = 1e3 + 10;
const int INF = 0x7fffffff;

int g[MAX_N][MAX_N];
int min[MAX_N];
int pre[MAX_N];
int n, m;
int s, t;

int EK_BFS()
{
    for (int i = 0; i < MAX_N; i++)
    {
        min[i] = INF;
        pre[i] = -1;
    }

    std::queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        const int u = q.front();
        q.pop();

        for (int v = 0; v <= n + 1; v++)
        {
            if (g[u][v] && pre[v] == -1)
            {
                pre[v] = u;
                min[v] = std::min(min[u], g[u][v]);
                q.push(v);
            }
        }
    }

    if (pre[t] == -1)
        return -1;
    return min[t];
}

int EK()
{
    int ans = 0;
    while (true)
    {
        const int res = EK_BFS();
        if (res == -1)
            break;

        int u = t;
        while (u != s)
        {
            g[u][pre[u]] += res;
            g[pre[u]][u] -= res;
            u = pre[u];
        }

        ans += res;
    }

    return ans;
}

int main()
{
    std::cin >> n >> m;

    s = 0;
    t = n + 1;
    for (int i = 1; i <= n; i++)
    {
        int c;
        std::cin >> c;
        if (c == 1)
            g[s][i] = 1;
        else
            g[i][t] = 1;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;
        g[u][v] = 1;
        g[v][u] = 1;
    }

    std::cout << EK();
    return 0;
}