#include <cstddef>
#include <iostream>

const int MAX_N = 2e3 + 10;

int map[MAX_N][MAX_N];
int r[MAX_N];
int c[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n;
    std::cin >> n;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            std::cin >> map[i][j];
    if (map[1][1] == 1)
    {
        std::cout << "1 1";
        return 0;
    }

    int const_c = map[1][n];
    for (int i = 2; i <= n; i++)
        const_c = const_c xor map[i][n];

    int const_r = map[n][1];
    for (int j = 2; j <= n; j++)
        const_r = const_r xor map[n][j];

    int wrong_r = 0;
    int wrong_c = 0;
    int wrong_r_num = 0;
    int wrong_c_num = 0;
    for (int i = 2; i <= n; i++)
    {
        int tmp_r = map[i][2];
        for (int j = 3; j <= n; j++)
            tmp_r = tmp_r xor map[i][j];
        tmp_r = tmp_r xor const_r;

        if (tmp_r != map[i][1])
        {
            wrong_r = i;
            wrong_r_num++;
        }
    }

    if (wrong_c == wrong_r == n)
    {
        std::cout << wrong_r << " " << wrong_c;
        return 0;
    }

    for (int j = 2; j <= n; j++)
    {
        int tmp_c = map[2][j];
        for (int i = 3; i <= n; i++)
            tmp_c = tmp_c xor map[i][j];
        tmp_c = tmp_c xor const_c;

        if (tmp_c != map[1][j])
        {
            wrong_c = j;
            wrong_c_num++;
        }
    }

    if (wrong_c_num == n - 2 and wrong_r_num == n - 2)
        std::cout << n << " " << n;
    else if (wrong_c_num == n - 2)
        std::cout << wrong_r << " " << n;
    else if (wrong_r_num == n - 2)
        std::cout << n << " " << wrong_c;
    else
        std::cout << wrong_r << " " << wrong_c;
    return 0;
}