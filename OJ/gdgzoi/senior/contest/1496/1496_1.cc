#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>

const int MAX_N = 1e5 + 10;

std::vector<int> g[MAX_N];

int in[MAX_N];
int in_tmp[MAX_N];
int out[MAX_N];
int cnt[MAX_N];

void bfs(int start)
{
    std::queue<int> q;
    q.push(start);
    cnt[start] = 1;

    while (!q.empty())
    {
        const int u = q.front();
        q.pop();

        for (std::size_t i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i];
            cnt[v] += cnt[u];
            in[v]--;
            if (in[v] == 0)
                q.push(v);
        }
    }
}

int main()
{
    int n, m;
    std::scanf("%d %d", &n, &m);

    for (int _i = 0; _i < m; _i++)
    {
        int u, v;
        std::scanf("%d %d", &u, &v);

        in[v]++;
        in_tmp[v]++;
        out[u]++;
        g[u].push_back(v);
    }

    for (int i = 1; i <= n; i++)
        if (in_tmp[i] == 0)
            bfs(i);

    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (out[i] == 0 && in_tmp[i] != 0)
            ans += cnt[i];

    std::printf("%d", ans);
    return 0;
}
