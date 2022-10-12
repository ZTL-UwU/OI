#include <iostream>
#include <cstring>
#include <cmath>

const int MAX_N = 1e3 + 10;
const int DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

bool map[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];
int n, m, c;

void dfs(int x, int y)
{
    vis[x][y] = true;

    for (int i = 0; i < 4; i++)
    {
        int xx = x + DIR[i][0];
        int yy = y + DIR[i][1];

        if (xx >= 0 && xx <= n && yy >= 0 && yy <= m && !vis[xx][yy] && !map[xx][yy])
            dfs(xx, yy);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        std::memset(map, 0, sizeof(map));
        std::memset(vis, 0, sizeof(vis));

        std::cin >> n >> m >> c;

        for (int i = 0; i < c; i++)
        {
            int x, y;
            std::cin >> x >> y;
            map[x][y] = true;
        }

        if (c == n * m || c == n * m - 1)
        {
            std::cout << "-1\n";
            continue;
        }

        if (c == n * m - 2)
        {
            int li = -1, lj = -1, flag = -1;
            for (int i = 1; i <= n; i++)
            {
                if (flag != -1)
                    break;
                for (int j = 1; j <= m; j++)
                {
                    if (!map[i][j])
                    {
                        if (li == -1 && lj == -1)
                        {
                            li = i;
                            lj = j;
                        }
                        else
                        {
                            flag = (int)(std::abs(i - li) + std::abs(j - lj) <= 1);
                            break;
                        }
                    }
                }
            }

            if (flag == 1)
                std::cout << "-1\n";
            else
                std::cout << "0\n";
            continue;
        }

        bool stop2 = false;
        for (int l = 1; l <= n; l++)
        {
            if (stop2)
                break;
            for (int k = 1; k <= m; k++)
            {
                if (!map[l][k])
                {
                    dfs(l, k);
                    stop2 = true;
                    break;
                }
            }
        }

        int tmp = 0;
        for (int l = 1; l <= n; l++)
            for (int k = 1; k <= m; k++)
                if (vis[l][k])
                    tmp++;

        if (tmp == n * m - c - 1)
        {
            std::cout << "0\n";
            continue;
        }

        int stop1 = -1;
        for (int i = 1; i <= n; i++)
        {
            if (stop1 != -1)
                break;
            for (int j = 1; j <= m; j++)
            {
                map[i][j] = true;

                std::memset(vis, 0, sizeof(vis));
                bool stop = false;
                for (int l = 1; l <= n; l++)
                {
                    if (stop)
                        break;
                    for (int k = 1; k <= m; k++)
                    {
                        if (!map[l][k])
                        {
                            dfs(l, k);
                            stop = true;
                            break;
                        }
                    }
                }

                int tmp = 0;
                for (int l = 1; l <= n; l++)
                    for (int k = 1; k <= m; k++)
                        if (vis[l][k])
                            tmp++;

                if (tmp == n * m - c - 1)
                {
                    stop1 = 1;
                    break;
                }

                map[i][j] = false;
            }
        }

        if (stop1 == 1)
            std::cout << "1\n";
        else
            std::cout << "2\n";
    }
    return 0;
}