#include <iostream>
#include <vector>

const int DIR[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const int INF = 0x7fffffff;
const int FULL_HP = 6;
const int MAX_N = 9;

struct cord
{
    int x;
    int y;
};

bool vis[MAX_N][MAX_N];
int mp[MAX_N][MAX_N];
int min_dis = INF;
cord start;
int w, h;

inline void dfs(cord c, int hp, int step)
{

    if (hp == 0 or step >= min_dis)
        return;
    if (mp[c.x][c.y] == 4)
        hp = FULL_HP;
    if (mp[c.x][c.y] == 3)
    {
        min_dis = step;
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        cord next;
        next.x = c.x + DIR[i][0];
        next.y = c.y + DIR[i][1];

        if (next.x >= 0 and next.x < h and next.y >= 0 and next.y < w and mp[next.x][next.y] != 0
            and not vis[next.x][next.y])
        {
            vis[c.x][c.y] = true;
            dfs(next, hp - 1, step + 1);
            vis[c.x][c.y] = false;
        }
    }
}

int main()
{
    std::cin >> w >> h;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            std::cin >> mp[i][j];
            if (mp[i][j] == 2)
            {
                start.x = i;
                start.y = j;
            }
        }
    }

    dfs(start, FULL_HP, 0);

    if (min_dis == INF)
        std::cout << "-1";
    else
        std::cout << min_dis;
    return 0;
}