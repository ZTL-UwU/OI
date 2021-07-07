#include <iostream>

const int MAX_NM = 3e3 + 10;

int matrix[MAX_NM][MAX_NM];
int diff[MAX_NM][MAX_NM];

int main()
{
    int n, m, q;
    std::cin >> n >> m >> q;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            std::cin >> matrix[i][j];

    for (int _i = 0; _i < q; _i++)
    {
        int x1, y1, x2, y2, val;
        std::cin >> x1 >> y1 >> x2 >> y2 >> val;

        for (int i = x1; i <= x2; i++)
        {
            diff[i][y1] += val;
            diff[i][y2 + 1] -= val;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        int diff_cnt = 0;
        for (int j = 1; j <= m; j++)
        {
            diff_cnt += diff[i][j];
            std::cout << matrix[i][j] + diff_cnt << " ";
        }

        std::cout << "\n";
    }

    return 0;
}