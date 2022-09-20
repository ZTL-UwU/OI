#include <iostream>
#include <cmath>

const int MAX_N = 1e3 + 10;
char map[MAX_N][MAX_N];

int main()
{
    int k;
    std::cin >> k;

    const int n7 = std::pow(k, 1.0 / 7);
    k -= std::pow(n7, 7);
    const int n6 = std::pow(k, 1.0 / 6);
    k -= std::pow(n6, 6);
    const int n5 = std::pow(k, 1.0 / 5);
    k -= std::pow(n5, 5);
    const int n4 = std::pow(k, 1.0 / 4);
    k -= std::pow(n4, 4);
    const int n3 = std::pow(k, 1.0 / 3);
    k -= std::pow(n3, 3);
    const int n2 = std::pow(k, 1.0 / 2);
    k -= std::pow(n2, 2);
    const int n1 = k;

    // std::cout << n6 << " " << n5 << " " << n4 << " " << n3 << " " << n2 << " " << n1 << "\n";
    for (int i = 0; i < MAX_N; i++)
        for (int j = 0; j < MAX_N; j++)
            map[i][j] = 'N';

    int n = 3;
    //----7
    for (int i = 0; i < n7; i++)
    {
        map[1][n + i] = 'Y';
        map[n + i][1] = 'Y';
    }
    n += n7;
    for (int i = 1; i < 7; i++)
    {
        for (int j = 0; j < n7; j++)
        {
            for (int l = 0; l < n7; l++)
            {
                map[n - j - n7 + l][n] = 'Y';
                map[n][n - j - n7 + l] = 'Y';
            }
            n++;
        }
    }
    for (int l = 0; l < n7; l++)
    {
        map[n - n7 + l][2] = 'Y';
        map[2][n - n7 + l] = 'Y';
    }
    //----6
    for (int i = 0; i < n6; i++)
    {
        map[1][n + i] = 'Y';
        map[n + i][1] = 'Y';
    }
    n += n6;
    for (int i = 1; i < 6; i++)
    {
        for (int j = 0; j < n6; j++)
        {
            for (int l = 0; l < n6; l++)
            {
                map[n - j - n6 + l][n] = 'Y';
                map[n][n - j - n6 + l] = 'Y';
            }
            n++;
        }
    }
    for (int l = 0; l < n6; l++)
    {
        map[n - n6 + l][n] = 'Y';
        map[n][n - n6 + l] = 'Y';
    }
    map[n][2] = 'Y';
    map[2][n] = 'Y';
    n++;
    //----5
    if (n5)
    {

        for (int i = 0; i < n5; i++)
        {
            map[1][n + i] = 'Y';
            map[n + i][1] = 'Y';
        }
        n += n5;
        for (int i = 1; i < 5; i++)
        {
            for (int j = 0; j < n5; j++)
            {
                for (int l = 0; l < n5; l++)
                {
                    map[n - j - n5 + l][n] = 'Y';
                    map[n][n - j - n5 + l] = 'Y';
                }
                n++;
            }
        }
        for (int l = 0; l < n5; l++)
        {
            map[n - n5 + l][n] = 'Y';
            map[n][n - n5 + l] = 'Y';
        }
        n++;
        map[n][n - 1] = 'Y';
        map[n - 1][n] = 'Y';
        map[n][2] = 'Y';
        map[2][n] = 'Y';
        n++;
    }
    //-----4
    if (n4)
    {

        for (int i = 0; i < n4; i++)
        {
            map[1][n + i] = 'Y';
            map[n + i][1] = 'Y';
        }
        n += n4;
        for (int i = 1; i < 4; i++)
        {
            for (int j = 0; j < n4; j++)
            {
                for (int l = 0; l < n4; l++)
                {
                    map[n - j - n4 + l][n] = 'Y';
                    map[n][n - j - n4 + l] = 'Y';
                }
                n++;
            }
        }
        for (int l = 0; l < n4; l++)
        {
            map[n - n4 + l][n] = 'Y';
            map[n][n - n4 + l] = 'Y';
        }
        n++;
        map[n][n - 1] = 'Y';
        map[n - 1][n] = 'Y';
        n++;
        map[n][n - 1] = 'Y';
        map[n - 1][n] = 'Y';
        // map[n][n - 1] = 'Y';
        // map[n - 1][n] = 'Y';
        map[n][2] = 'Y';
        map[2][n] = 'Y';
        n++;
    }
    //-----3
    if (n3)
    {

        for (int i = 0; i < n3; i++)
        {
            map[1][n + i] = 'Y';
            map[n + i][1] = 'Y';
        }
        n += n3;
        for (int i = 1; i < 3; i++)
        {
            for (int j = 0; j < n3; j++)
            {
                for (int l = 0; l < n3; l++)
                {
                    map[n - j - n3 + l][n] = 'Y';
                    map[n][n - j - n3 + l] = 'Y';
                }
                n++;
            }
        }
        for (int l = 0; l < n3; l++)
        {
            map[n - n3 + l][n] = 'Y';
            map[n][n - n3 + l] = 'Y';
        }
        n++;
        map[n][n - 1] = 'Y';
        map[n - 1][n] = 'Y';
        n++;
        map[n][n - 1] = 'Y';
        map[n - 1][n] = 'Y';
        n++;
        map[n][n - 1] = 'Y';
        map[n - 1][n] = 'Y';
        // n++;
        // map[n][n - 1] = 'Y';
        // map[n - 1][n] = 'Y';
        map[n][2] = 'Y';
        map[2][n] = 'Y';
        n++;
    }
    //-----2
    if (n2)
    {

        for (int i = 0; i < n2; i++)
        {
            map[1][n + i] = 'Y';
            map[n + i][1] = 'Y';
        }
        n += n2;
        for (int i = 1; i < 2; i++)
        {
            for (int j = 0; j < n2; j++)
            {
                for (int l = 0; l < n2; l++)
                {
                    map[n - j - n2 + l][n] = 'Y';
                    map[n][n - j - n2 + l] = 'Y';
                }
                n++;
            }
        }
        for (int l = 0; l < n2; l++)
        {
            map[n - n2 + l][n] = 'Y';
            map[n][n - n2 + l] = 'Y';
        }
        n++;
        map[n][n - 1] = 'Y';
        map[n - 1][n] = 'Y';
        n++;
        map[n][n - 1] = 'Y';
        map[n - 1][n] = 'Y';
        n++;
        map[n][n - 1] = 'Y';
        map[n - 1][n] = 'Y';
        n++;
        map[n][n - 1] = 'Y';
        map[n - 1][n] = 'Y';
        // n++;
        // map[n][n - 1] = 'Y';
        // map[n - 1][n] = 'Y';
        map[n][2] = 'Y';
        map[2][n] = 'Y';
        n++;
        // std::cout << n + 4 << "\n";
        // for (int i = 1; i <= n + 4; i++)
        // {
        //     for (int j = 1; j <= n + 4; j++)
        //         std::cout << map[i][j];
        //     std::cout << "\n";
        // }
        // return 0;
    }
    //-----1
    if (n1)
    {

        for (int i = 0; i < n1; i++)
        {
            map[n][1] = 'Y';
            map[1][n] = 'Y';
            n++;
            for (int j = 1; j < 7; j++)
            {
                map[n][n - 1] = 'Y';
                map[n - 1][n] = 'Y';
                n++;
            }
            map[n - 1][2] = 'Y';
            map[2][n - 1] = 'Y';
            n++;
        }
    }

    std::cout << n << "\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            std::cout << map[i][j];
        std::cout << "\n";
    }
    return 0;
}