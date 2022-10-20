#include <iostream>

const int MAX_N = 1e3;

bool map[MAX_N][MAX_N];

int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char ch;
            std::cin >> ch;

            if (ch == '#')
                map[i][j] = true;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m - 1; j++)
        {
            if (i % 2 == 0 || j == 0 || map[i][j])
                std::cout << "#";
            else
                std::cout << ".";
        }
        std::cout << ".";
        std::cout << "\n";
    }

    std::cout << "\n";

    for (int i = 0; i < n; i++)
    {
        std::cout << ".";
        for (int j = 1; j < m; j++)
        {
            if (i % 2 == 1 || j == m - 1 || map[i][j])
                std::cout << "#";
            else
                std::cout << ".";
        }
        std::cout << "\n";
    }
    return 0;
}