#include <iostream>

using i64 = long long;

const int MAX_Q = 5e4 + 10;
const int MOD = 1e9 + 7;
const int MAX_N = 2010;

i64 a[MAX_N + 10][MAX_N + 10];
int n[MAX_Q];

int main()
{
    int t;
    std::cin >> t;

    int max = 0;
    for (int i = 0; i < t; i++)
    {
        std::cin >> n[i];
        max = std::max(max, n[i]);
    }

    a[1][0] = 1;
    a[2][0] = 1;
    a[2][1] = 1;

    for (int i = 3; i <= max + 1; i++)
    {
        for (int j = 1; j < i; j++)
        {
            i64 tmp = 0;
            for (int k = i - 2; k >= j - 1; k--)
                tmp = (tmp + a[i - 1][k]) % MOD;

            a[i][j] = tmp;
        }

        a[i][0] = a[i][1];
    }

    for (int i = 0; i < t; i++)
        std::cout << a[n[i] + 1][0] << "\n";
    return 0;
}