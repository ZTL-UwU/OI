#include <iostream>
#include <cstring>
#include <cstdio>

const int MAX_N = 2e2;
const int MAX_M = 2e1;
const int DIR[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

char board[MAX_N][MAX_M];
bool vis1[MAX_N][MAX_M];
bool vis[MAX_N][MAX_M];
int n, m = 10, k;

inline bool check(int x, int y, char color, bool do_clear)
{
    if (x >= 0 and y >= 0 and x < n and y < m and (do_clear ? (not vis1[x][y]) : (not vis[x][y]))
        and board[x][y] == color)
        return true;
    return false;
}

inline int dfs(int x, int y, bool do_clear)
{
    if (do_clear)
        vis1[x][y] = true;
    else
        vis[x][y] = true;

    int res = 1;
    for (int i = 0; i < 4; i++)
    {
        int xx = x + DIR[i][0];
        int yy = y + DIR[i][1];

        if (check(xx, yy, board[x][y], do_clear))
            res += dfs(xx, yy, do_clear);
    }

    if (do_clear)
        board[x][y] = '0';
    return res;
}

inline bool clear()
{
    memset(vis, 0, sizeof(vis));
    memset(vis1, 0, sizeof(vis1));

    bool res = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] != '0' and (not vis[i][j]))
            {
                if (dfs(i, j, false) >= k)
                {
                    dfs(i, j, true);
                    res = true;
                }
            }
        }
    }

    return res;
}

inline void fall()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = n - 2; j >= 0; j--)
        {
            if (board[j][i] != '0')
            {
                int l = j;
                while (l < n - 1 and board[l + 1][i] == '0')
                {
                    std::swap(board[l][i], board[l + 1][i]);
                    l++;
                }
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> k;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < 10; j++)
            std::cin >> board[i][j];

    while (clear())
        fall();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 10; j++)
            std::cout << board[i][j];
        std::cout << "\n";
    }
    return 0;
}