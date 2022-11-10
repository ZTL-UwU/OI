#include <iostream>

const int MAX_N = 1e3 + 10;
const int DIR[8][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};

bool vis[MAX_N][MAX_N];
int map[MAX_N][MAX_N];
int n;

int ans = -1;
void dfs(int x, int y, const int base)
{
    for (int i = 0; i < 8; i++)
    {
        int xxx = x + DIR[i][0];
        int yyy = y + DIR[i][1];
        if (xxx >= 0 && xxx < n && yyy >= 0 && yyy < n)
        {
            if (ans == -1)
            {
                if (map[xxx][yyy] < base)
                    ans = 0;
                if (map[xxx][yyy] > base)
                    ans = 1;
            }
            else
            {
                if (ans == 0 && map[xxx][yyy] > base)
                    ans = 2;
                if (ans == 1 && map[xxx][yyy] < base)
                    ans = 2;
            }
        }
    }

    if (ans == 2)
        return;

    for (int i = 0; i < 8; i++)
    {
        int xx = x + DIR[i][0];
        int yy = y + DIR[i][1];

        if (!vis[xx][yy] && xx >= 0 && xx < n && yy >= 0 && yy < n && map[xx][yy] == base)
        {
            vis[xx][yy] = true;
            dfs(xx, yy, base);
        }
    }
}

int main()
{
    std::cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::cin >> map[i][j];

    int peak = 0;
    int valley = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!vis[i][j])
            {
                ans = -1;
                vis[i][j] = true;
                dfs(i, j, map[i][j]);

                if (ans == 0)
                    peak++;
                if (ans == 1)
                    valley++;
                if (ans == -1)
                {
                    peak++;
                    valley++;
                }
            }
        }
    }

    std::cout << peak << " " << valley;
    return 0;
}