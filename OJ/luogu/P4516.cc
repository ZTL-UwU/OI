#include <iostream>
#include <cstring>
#include <vector>

const int MAX_N = 1e5 + 10;
const int MAX_K = 1e2 + 10;
const int MOD = 1000000007;

std::vector<int> tree[MAX_N];
int dp[MAX_N][MAX_K][2][2];
int size[MAX_N];
int n, k;

inline long long int add(long long int a, long long int b) { return (a + b) % MOD; }
inline long long int mul(long long int a, long long int b) { return (a * b) % MOD; }

inline void get_dp(int u, int fa)
{
    size[u] = 1;
    dp[u][0][0][0] = 1;
    dp[u][1][1][0] = 1;

    for (auto v : tree[u])
    {
        if (v == fa)
            continue;
        get_dp(v, u);

        for (int i = 0; i <= std::min(size[u], k); i++)
        {
            dp[0][i][0][0] = 1;
            dp[0][i][0][1] = 1;
            dp[0][i][1][0] = 1;
            dp[0][i][1][1] = 1;
        }

        for (int i = 0; i <= std::min(size[u], k); i++)
        {
            for (int j = 0; j <= std::min(size[v], k - i); j++)
            {
                dp[0][i + j][0][0] = add(dp[0][i + j][0][0], mul(dp[u][i][0][0], dp[v][j][0][1]));

                dp[0][i + j][0][1] =
                    add(dp[0][i + j][0][1], add(mul(dp[u][i][0][1], add(dp[v][j][0][1], dp[v][j][1][1])),
                                                mul(dp[u][i][0][0], dp[v][j][1][1])));

                dp[0][i + j][1][0] = add(dp[0][i + j][1][0], mul(dp[u][i][1][0], add(dp[v][j][0][0], dp[v][j][0][1])));

                dp[0][i + j][1][1] =
                    add(dp[0][i + j][1][1], add(mul(dp[u][i][1][0], add(dp[v][j][1][0], dp[v][j][1][1])),
                                                mul(dp[u][i][1][1], add(add(dp[v][j][0][0], dp[v][j][0][1]),
                                                                        add(dp[v][j][1][0], dp[v][j][1][1])))));
            }
        }

        size[u] += size[v];
        for (int i = 0; i <= std::min(size[u], k); i++)
        {
            dp[u][i][0][0] = dp[0][i][0][0];
            dp[u][i][0][1] = dp[0][i][0][1];
            dp[u][i][1][0] = dp[0][i][1][0];
            dp[u][i][1][1] = dp[0][i][1][1];
        }
    }
}

int main()
{
    std::cin >> n >> k;

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        std::cin >> u >> v;

        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    get_dp(1, 0);

    std::cout << add(dp[1][k][0][1], dp[1][k][1][1]);
    return 0;
}