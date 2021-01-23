#include <algorithm>
#include <iostream>
#include <cstring>

const int MAX_N = 2.1e3;

int ans[MAX_N][MAX_N];
int w[MAX_N];
int n, m;

int solve()
int main()
{
    std::cin >> n >> m;

    for (int i = 0; i < n; i++)
        std::cin >> w[i];

    std::sort(w, w + n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (ans[i][j] != 0)
                std::cout << ans[i][j];
            else
                std::cout << (ans[i][j] = solve(i, j));
        }

        std::cout << "\n";
    }
    return 0;
}