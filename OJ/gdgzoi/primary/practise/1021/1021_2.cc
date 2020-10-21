#include <iostream>
#include <string.h>
#include <stdio.h>

const int MAXN = 1e3 + 10;
int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
bool map[MAXN][MAXN];
bool vis[MAXN][MAXN];
int n, m;
int ans;

void dfs(int x, int y)
{
    ans++;
    vis[x][y] = true;
    for (int i = 0; i < 4; i++)
    {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        if (xx >= 0 && xx < n && yy >= 0 && yy < m && !vis[xx][yy] && map[xx][yy])
            dfs(xx, yy);
    }
}

void init()
{
    memset(vis, 0, sizeof(vis));
    memset(map, 0, sizeof(map));
    ans = 0;
}

int main()
{
    while (1)
    {
        init();

        std::cin >> m >> n;
        if (n == 0 && m == 0)
            return 0;

        int startx, starty;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                char ch;
                std::cin >> ch;
                if (ch == '.')
                    map[i][j] = true;
                if (ch == '#')
                    map[i][j] = false;
                if (ch == '@')
                {
                    startx = i;
                    starty = j;
                }
            }
        }

        dfs(startx, starty);

        std::cout << ans << "\n";
    }
    return 0;
}