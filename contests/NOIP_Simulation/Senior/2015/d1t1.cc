#include <iostream>
#include <stdio.h>

const int MAXN = 100;
int ans[MAXN][MAXN];

int main()
{
    int n;
    std::cin >> n;

    ans[1][(n + 1) / 2] = 1;
    int last_x = 1;
    int last_y = (n + 1) / 2;
    for (int i = 2; i <= n * n; i++)
    {
        if (last_x == 1 && last_y != n)
        {
            ans[n][last_y + 1] = i;
            last_x = n;
            last_y++;
        }
        else if (last_x != 1 && last_y == n)
        {
            ans[last_x - 1][1] = i;
            last_x--;
            last_y = 1;
        }
        else if (last_x == 1 && last_y == n)
        {
            ans[last_x + 1][last_y] = i;
            last_x++;
        }
        else if (!ans[last_x - 1][last_y + 1])
        {
            ans[last_x - 1][last_y + 1] = i;
            last_x--;
            last_y++;
        }
        else
        {
            ans[last_x + 1][last_y] = i;
            last_x++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            std::cout << ans[i][j] << " ";
        std::cout << "\n";
    }
    return 0;
}