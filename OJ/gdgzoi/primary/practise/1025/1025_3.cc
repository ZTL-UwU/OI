#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cstdio>

const int MAX_N = 2e2;

int beauty[MAX_N][MAX_N];
int pre[MAX_N][MAX_N];
int dp[MAX_N][MAX_N];

inline void dfs(int f, int route)
{
    if (f == 1)
    {
        std::cout << route << " ";
        return;
    }

    dfs(f - 1, pre[f][route]);
    std::cout << route << " ";
}

int main()
{
    int f, v;
    std::cin >> f >> v;

    for (int i = 1; i <= f; i++)
        for (int j = 1; j <= v; j++)
            std::cin >> beauty[i][j];

    for (int i = 1; i <= v - f; i++)
    {
        dp[1][i] = beauty[1][i];
        pre[1][i] = i;
    }

    for (int i = 2; i <= f; i++)
    {
        for (int j = i; j <= v - (f - i); j++)
        {
            for (int k = 1; k < j; k++)
            {
                if (dp[i - 1][k] + beauty[i][j] > dp[i][j])
                {
                    dp[i][j] = dp[i - 1][k] + beauty[i][j];
                    pre[i][j] = k;
                }
            }
        }
    }

    int ans = -1;
    int ans_route;
    for (int i = f; i <= v; i++)
    {
        if (dp[f][i] > ans)
        {
            ans = dp[f][i];
            ans_route = i;
        }
    }

    std::cout << ans << "\n";
    dfs(f, ans_route);
    return 0;
}