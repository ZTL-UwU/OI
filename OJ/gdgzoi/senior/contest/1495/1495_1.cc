#include <iostream>
#include <cstdio>

const int MAX_N = 2e3 + 10;

int h_edge_cnt[MAX_N][MAX_N];
int v_edge_cnt[MAX_N][MAX_N];
int node_cnt[MAX_N][MAX_N];
bool color[MAX_N][MAX_N];
char str[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m, q;
    std::scanf("%d %d %d", &n, &m, &q);

    for (int i = 1; i <= n; i++)
    {
        std::scanf("%s", str + 1);

        for (int j = 1; j <= m; j++)
        {
            color[i][j] = str[j] - '0';

            node_cnt[i][j] = color[i][j] + node_cnt[i - 1][j] + node_cnt[i][j - 1] - node_cnt[i - 1][j - 1];
            v_edge_cnt[i][j] =
                color[i - 1][j] * color[i][j] + v_edge_cnt[i - 1][j] + v_edge_cnt[i][j - 1] - v_edge_cnt[i - 1][j - 1];
            h_edge_cnt[i][j] =
                color[i][j - 1] * color[i][j] + h_edge_cnt[i - 1][j] + h_edge_cnt[i][j - 1] - h_edge_cnt[i - 1][j - 1];
        }
    }

    for (int _i = 0; _i < q; _i++)
    {
        int x1, y1, x2, y2;
        std::scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        int ans = node_cnt[x2][y2] - node_cnt[x1 - 1][y2] - node_cnt[x2][y1 - 1] + node_cnt[x1 - 1][y1 - 1];
        ans -= v_edge_cnt[x2][y2] - v_edge_cnt[x1][y2] - v_edge_cnt[x2][y1 - 1] + v_edge_cnt[x1][y1 - 1];
        ans -= h_edge_cnt[x2][y2] - h_edge_cnt[x1 - 1][y2] - h_edge_cnt[x2][y1] + h_edge_cnt[x1 - 1][y1];

        std::printf("%d\n", ans);
    }
    return 0;
}
