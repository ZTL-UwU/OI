#include <algorithm>
#include <cstdio>

const int INF = 0x7fffffff;
const int MAX_N = 1e3 + 10;

struct cord
{
    int x;
    int y;

    cord(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator!=(cord c) { return not(this->x == c.x and this->y == c.y); }
};

int a[MAX_N][MAX_N];
int been[MAX_N];

int main()
{
    std::freopen("pacman.in", "r", stdin);
    std::freopen("pacman.out", "w", stdout);

    int n;
    std::scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::scanf("%d", &a[i][j]);

    for (int i = 1; i < n - 1; i++)
    {
        bool first_flag = true;
        cord pacman = cord(i, 0);
        cord delta = cord(-1, 1);
        int been_count = 0;

        while (first_flag or pacman != cord(i, 0))
        {
            first_flag = false;

            cord next = cord(pacman.x + delta.x, pacman.y + delta.y);

            // Ceiling
            if (next.x == 0)
                delta.x = 1;
            // Right
            if (next.y == n - 1)
                delta.y = -1;
            // Floor
            if (next.x == n - 1)
                delta.x = -1;

            pacman = next;
            been_count += a[pacman.x][pacman.y];
        }

        been[i] = been_count;
    }

    for (int i = 0; i < n; i++)
    {
        been[0] += a[i][i];
        been[n - 1] += a[i][n - 1 - i];
    }

    int max = -INF;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int intersection_count = 0;

            if ((j - i) % 2 == 0)
            {
                if (i == 0)
                    intersection_count = a[j / 2][j / 2] + a[n - 1 - j / 2][n - 1 - j / 2];
                else if (j == n - 1)
                    intersection_count =
                        a[(n - 1 - j) / 2][n - 1 - (n - 1 - j) / 2] + a[n - 1 - (n - 1 - j) / 2][(n - 1 - j) / 2];
                else
                    intersection_count = a[j - (j - 1) / 2][(j - i) / 2] + a[(j - 1) / 2][i + (j - i) / 2]
                                         + a[n - 1 - (j - i) / 2][n - 1 - j + (j - i) / 2]
                                         + a[n - 1 - i - (j - i) / 2][n - 1 - (j - i) / 2];
            }

            max = std::max(max, been[i] + been[j] - intersection_count);
        }
    }

    std::printf("%d", max);
    return 0;
}