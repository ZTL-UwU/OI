#include <iostream>
#include <stdio.h>

const int MAXN = 1e2 + 10;
bool like[MAXN][MAXN];
bool used[MAXN];
int ans;
int n;

inline void dfs(int x)
{
    if (x == n)
    {
        ans++;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!used[i] && like[x][i])
        {
            used[i] = true;
            dfs(x + 1);
            used[i] = false;
        }
    }
}

int main()
{
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char ch;
            std::cin >> ch;
            if (ch == '0')
                like[i][j] = false;
            else
                like[i][j] = true;
        }
    }

    dfs(0);

    std::cout << ans;
    return 0;
}