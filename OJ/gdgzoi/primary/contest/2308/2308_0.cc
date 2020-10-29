#include <iostream>
#include <cstring>
#include <cstdio>

const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int MAX_N = 1e2;

char map[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];
int ans = 0;
int n, m;

inline bool check(int x, int y)
{
    if (x >= 0 and y >= 0 and x < n and y < m and (not vis[x][y]) and map[x][y] != '#')
        return true;
    return false;
}

inline void dfs(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];

        if (check(xx, yy))
        {
            ans++;
            vis[xx][yy] = true;
            dfs(xx, yy);
        }
    }
}

int main()
{
    std::cin >> m >> n;

    int startx, starty;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cin >> map[i][j];
            if (map[i][j] == '@')
            {
                startx = i;
                starty = j;
            }
        }
    }

    dfs(startx, starty);

    std::cout << ans;
    return 0;
}