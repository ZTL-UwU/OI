#include <iostream>
#include <cstdio>

const int MOD = 998244353;
const int MAX_N = 1010;
using i64 = long long;

int a[MAX_N][MAX_N];
i64 f[MAX_N][MAX_N];
i64 f1[MAX_N][MAX_N];

int main()
{
    std::freopen("plant.in", "r", stdin);
    std::freopen("plant.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int T, id;
    std::cin >> T >> id;

    for (int _i = 0; _i < T; _i++)
    {
        int n, m, C, F;
        std::cin >> n >> m >> C >> F;

        char ch;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                std::cin >> ch;
                a[i][j] = ch - '0';
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                if (a[i][j] == 1)
                    f[i][j] = -1;
                else if (j == m - 1)
                    f[i][j] = 0;
                else
                    f[i][j] = f[i][j + 1] + 1;
            }
        }

        if (F)
        {
            for (int j = 0; j < m; j++)
            {
                for (int i = n - 1; i >= 0; i--)
                {
                    if (a[i][j] == 1)
                        f1[i][j] = -1;
                    else if (i == n - 1)
                        f1[i][j] = 0;
                    else
                        f1[i][j] = f1[i + 1][j] + 1;
                }
            }
        }

        i64 vc = 0;
        i64 vf = 0;

        if (C)
        {
            for (int j = 0; j < m - 1; j++)
            {
                for (int i = 0; i < n - 2; i++)
                {
                    if (a[i][j] == 0 && a[i + 1][j] == 0 && f[i][j] > 0)
                    {
                        for (int k = i + 2; k < n; k++)
                        {
                            if (a[k][j] == 1)
                                break;
                            if (f[k][j] > 0)
                                vc = (vc + (f[i][j] * f[k][j]) % MOD) % MOD;
                        }
                    }
                }
            }
        }

        if (F)
        {
            for (int j = 0; j < m - 1; j++)
            {
                for (int i = 0; i < n - 3; i++)
                {
                    if (a[i][j] == 0 && a[i + 1][j] == 0 && f[i][j] > 0)
                    {
                        for (int k = i + 2; k < n - 1; k++)
                        {
                            if (a[k][j] == 1)
                                break;
                            if (f[k][j] > 0 && f1[k][j])
                                vf = (vf + (((f[i][j] * f[k][j]) % MOD) * f1[k][j]) % MOD) % MOD;
                        }
                    }
                }
            }
        }

        std::cout << (C * vc) % MOD << " " << (F * vf) % MOD << "\n";
    }

    return 0;
}
