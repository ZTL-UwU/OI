#include <iostream>

const int MAX_N = 1e2 + 10;
const int MAX_M = 1e4 + 10;

int dis[MAX_N][MAX_N];
int a[MAX_M];
int n, m;

void floyd()
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dis[i][j] > dis[i][k] + dis[k][j])
                    dis[i][j] = dis[i][k] + dis[k][j];
}

int main()
{
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
        std::cin >> a[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            std::cin >> dis[i][j];
    floyd();

    int ans = 0;
    for (int i = 0; i < m - 1; i++)
        ans += dis[a[i] - 1][a[i + 1] - 1];
    std::cout << ans;
    return 0;
}
