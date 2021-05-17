#include <iostream>
#include <cstring>

const int INF = 0x7fffffff;
const int MAX_W = 1e3 + 10;
const int MAX_N = 5e2;
const int TIMES = 1e3;

long long int dp[MAX_W];
int w[MAX_N];
int t[MAX_N];
int N, W;

bool check(int key)
{
    std::memset(dp, -127, sizeof(dp));

    dp[0] = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = W; j >= 0; j--)
        {
            const int k = std::min(W, j + w[i]);
            dp[k] = std::max(dp[k], dp[j] + t[i] - (long long int)w[i] * key);
        }
    }

    return dp[W] >= 0;
}

int main()
{
    std::cin >> N >> W;

    for (int i = 0; i < N; i++)
    {
        std::cin >> w[i] >> t[i];
        t[i] *= TIMES;
    }

    int l = TIMES;
    int r = INF - l;
    while (l <= r)
    {
        const int mid = (l + r) / 2;

        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }

    std::cout << r;
    return 0;
}
