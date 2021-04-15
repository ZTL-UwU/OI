#include <iostream>
#include <cstring>
#include <queue>

const int MAX_N = 1e3 + 10;
const int MAX_2N = 2 * MAX_N;
const int S = 0;
int T;

int g[MAX_2N][MAX_2N];
int a[MAX_N][MAX_N];
int min[MAX_2N];
int pre[MAX_2N];
int r[MAX_N];
int c[MAX_N];
int n;

int EK_bfs()
{
    std::memset(min, 0x7f, sizeof(min));
    std::memset(pre, -1, sizeof(pre));

    std::queue<int> q;
    q.push(S);

    while (not q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 1; i <= T; i++)
        {
            if (g[u][i] != 0 and pre[i] == -1)
            {
                min[i] = std::min(min[u], g[u][i]);
                pre[i] = u;

                q.push(i);
            }
        }
    }

    if (pre[T] == -1)
        return -1;
    return min[T];
}

void EK()
{
    while (true)
    {
        int max_flow = EK_bfs();
        if (max_flow == -1)
            break;

        int u = T;
        while (u != S)
        {
            g[pre[u]][u] -= max_flow;
            g[u][pre[u]] += max_flow;
            u = pre[u];
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n;
    T = n * 2 + 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            std::cin >> a[i][j];

            if (a[i][j] % 2 == 1)
            {
                g[i][n + j] = 1;
                r[i]++;
                c[j]++;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        g[S][i] = r[i] / 2;
        g[n + i][T] = c[i] / 2;
    }

    EK();

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i][j] % 2 == 0)
                std::cout << a[i][j] / 2 << " ";
            else
                std::cout << a[i][j] / 2 + g[i][n + j] << " ";
        }
        std::cout << "\n";
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i][j] % 2 == 0)
                std::cout << a[i][j] / 2 << " ";
            else
                std::cout << a[i][j] - (a[i][j] / 2 + g[i][n + j]) << " ";
        }
        std::cout << "\n";
    }
    return 0;
}