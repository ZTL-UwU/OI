#include <iostream>
#include <cstdio>

const int MAX_N = 550;

bool g[MAX_N][MAX_N];
bool used[MAX_N];
int v[MAX_N];
int n, m;

void dfs(int k)
{
    if (k == n + 1)
    {
        int cnt = 0;
        for (int i = 2; i < n; i++)
            if (g[v[i]][v[i - 1]] != g[v[i]][v[i + 1]])
                cnt++;

        if (cnt <= 1)
        {
            for (int i = 1; i <= n; i++)
                std::cout << v[i] << " ";
            exit(0);
        }
        return;
    }

    if (k == 1)
    {
        used[1] = true;
        v[k] = 1;
        dfs(k + 1);
        used[1] = false;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            if (!used[i])
            {
                used[i] = true;
                v[k] = i;
                dfs(k + 1);
                used[i] = false;
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y;
        std::cin >> x >> y;
        g[x][y] = true;
        g[y][x] = true;
    }

    dfs(1);
    return 0;
}