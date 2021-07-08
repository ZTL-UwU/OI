#include <iostream>
#include <vector>
#include <queue>

struct QueData
{
    int pos;
    bool color;
};

const int MAX_N = 1e5 + 10;

std::vector<int> g[MAX_N];
bool color[MAX_N];
bool vis[MAX_N];
long long ans;
int n, m;

bool check_out_degree()
{
    for (int i = 1; i <= n; i++)
        if (g[i].size() >= 2)
            return false;
    return true;
}

bool bfs(int start)
{
    std::queue<QueData> q;
    q.push({start, false});
    color[start] = false;
    vis[start] = true;
    int cnt_black = 1;
    int cnt_white = 0;
    bool res = true;

    while (!q.empty())
    {
        const auto u = q.front();
        q.pop();

        for (auto v : g[u.pos])
        {
            if (!vis[v])
            {
                q.push({v, !u.color});
                vis[v] = true;
                color[v] = !u.color;

                if (color[v])
                    cnt_white++;
                else
                    cnt_black++;
            }

            if (color[v] == u.color)
                res = false;
        }
    }

    ans += 1LL * cnt_white * (cnt_white - 1) / 2 + 1LL * cnt_black * (cnt_black - 1) / 2;

    return res;
}

bool check_odd_cycle()
{
    bool flag = true;
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            flag = flag && bfs(i);

    return flag;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m;

    for (int _i = 0; _i < m; _i++)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (m == 0)
        std::cout << "3 " << 1LL * n * (n - 1) * (n - 2) / 6;
    else if (check_out_degree())
        std::cout << "2 " << 1LL * m * (n - 2);
    else if (check_odd_cycle())
        std::cout << "1 " << ans;
    else
        std::cout << "0 1";
    return 0;
}