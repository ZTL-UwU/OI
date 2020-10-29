#include <iostream>
#include <cstring>
#include <cstdio>

const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int MAX_N = 1e3;

bool map[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];
int n, m;

inline bool check(int x, int y)
{
    if (x >= 0 and y >= 0 and x < n and y < m and (not vis[x][y]) and map[x][y])
        return true;
    return false;
}

inline int dfs(int x, int y)
{
    int res = 1;
    for (int i = 0; i < 4; i++)
    {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];

        if (check(xx, yy))
        {
            vis[xx][yy] = true;
            res += dfs(xx, yy);
        }
    }

    return res;
}

int main()
{
    std::cin >> n >> m;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            std::cin >> map[i][j];

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if ((not vis[i][j]) and map[i][j])
                ans = std::max(ans, dfs(i, j));

    if (ans > 1)
        ans--;

    std::cout << ans;
    return 0;
}