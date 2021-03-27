#include <cstring>
#include <cstdio>

const int INF = 0x7fffffff;
const int MAX_N = 3e2;

struct cord
{
    int x;
    int y;

    cord() {}
    cord(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator==(cord c) { return this->x == c.x and this->y == c.y; }
};

// true: wall
bool map[MAX_N][MAX_N];
bool vis[MAX_N][MAX_N];
int min_step = INF;

/*
 * dir: 1: up
 *      2: right
 *      3: down
 *      4: left
 */
void dfs(cord a, cord b, int step, int last_dir)
{
    if (step >= min_step)
        return;

    if (a == b)
    {
        min_step = step;
        return;
    }

    for (int i = 1; i <= 4; i++)
    {
        if (i == last_dir)
            continue;

        bool flag = true;
        cord next_a = a;
        while (true)
        {

            if (vis[next_a.x][next_a.y])
                flag = false;
            vis[next_a.x][next_a.y] = true;

            cord tmp = next_a;
            tmp.x -= (i == 1);
            tmp.x += (i == 3);
            tmp.y += (i == 2);
            tmp.y -= (i == 4);

            if (map[tmp.x][tmp.y])
                break;
            next_a = tmp;
        }

        cord next_b = b;
        while (true)
        {
            if (vis[next_b.x][next_b.y])
                flag = false;
            vis[next_b.x][next_b.y] = true;

            cord tmp = next_b;
            tmp.x -= (i == 1);
            tmp.x += (i == 3);
            tmp.y += (i == 2);
            tmp.y -= (i == 4);

            if (map[tmp.x][tmp.y])
                break;
            next_b = tmp;
        }

        std::printf("%d %d : %d %d\n", next_a.x, next_a.y, next_b.x, next_b.y);

        if (flag)
            dfs(next_a, next_b, step + 1, i);

        while (true)
        {
            vis[next_a.x][next_a.y] = true;

            cord tmp = next_a;
            tmp.x += (i == 1);
            tmp.x -= (i == 3);
            tmp.y -= (i == 2);
            tmp.y += (i == 4);

            if (map[tmp.x][tmp.y])
                break;
            next_a = tmp;
        }

        while (true)
        {
            vis[next_b.x][next_b.y] = false;

            cord tmp = next_b;
            tmp.x += (i == 1);
            tmp.x -= (i == 3);
            tmp.y -= (i == 2);
            tmp.y += (i == 4);

            if (map[tmp.x][tmp.y])
                break;
            next_b = tmp;
        }
    }
}

int main()
{
    std::freopen("ball.in", "r", stdin);
    std::freopen("ball.out", "w", stdout);

    int n, m, q;
    std::scanf("%d %d %d", &n, &m, &q);

    for (int i = 0; i <= n + 1; i++)
    {
        map[0][i] = true;
        map[i][0] = true;
        map[n + 1][i] = true;
        map[i][n + 1] = true;
    }

    for (int _i = 0; _i < m; _i++)
    {
        int x, y;
        std::scanf("%d %d", &x, &y);

        map[x][y] = true;
    }

    for (int _i = 0; _i < q; _i++)
    {
        cord a, b;
        std::scanf("%d %d %d %d", &a.x, &a.y, &b.x, &b.y);

        if (a == b)
        {
            std::printf("0\n");
            continue;
        }

        std::memset(vis, 0, sizeof(vis));
        dfs(a, b, 0, 0);
        std::printf("%d\n", min_step);
    }
    return 0;
}