#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

const int MAXN = 10;
const int MAX_STATE = 1 << MAXN;

std::vector<int> state;
int dp[MAXN][MAX_STATE];
int n, k;

inline void get_state()
{
    for (int i = 0; i < (1 << n); i++)
        if (!(i & (i << 1))) // Last digit
            state.push_back(i);
}

inline int count_one(int sta)
{
    int ans = 0;
    while (sta)
    {
        if (sta % 2)
            ans++;
        sta /= 2;
    }

    return ans;
}

inline void get_dp()
{
    for (int i = 0; i < state.size(); i++)
        dp[0][i] = count_one(state[i]);

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < state.size(); j++)
        {
            for (int k = 0; k < state.size(); k++)
            {
                if (state[j] & state[k] or state[j] & (state[k] << 1) or state[j] & (state[k] >> 1))
                    continue;

                dp[i][j] = std::max(dp[i][j], dp[i - 1][k] + count_one(state[j]));
            }
        }
    }
}

int main()
{
    std::cin >> n;
    get_state();
    get_dp();

    int ans = -1;
    for (int i = 0; i < state.size(); i++)
        ans = std::max(ans, dp[n - 1][i]);

    std::cout << ans;
    return 0;
}