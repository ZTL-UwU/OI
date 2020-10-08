#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

const int MAXN = 10;
const int MAX_STATE = 1 << MAXN;
std::vector<int> state;
long long dp[MAXN][MAX_STATE][MAX_STATE]; // [row][state][choosen]
size_t n, m;

inline void get_state()
{
    for (int i = 0; i < (1 << n); i++)
        if (!(i & (i << 1))) // Last digit
            state.push_back(i);
}

inline int count_one(int sta)
{
    int res = 0;
    while (sta)
    {
        if (sta % 2)
            res++;
        sta /= 2;
    }

    return res;
}

inline void get_dp()
{
    for (size_t i = 0; i < state.size(); i++)
        dp[0][i][count_one(state[i])] = 1;

    for (size_t i = 1; i < n; i++)
    {
        for (size_t j = 0; j < state.size(); j++)
        {
            for (size_t k = 0; k < state.size(); k++)
            {
                if (state[j] & state[k] or state[j] & (state[k] << 1) or state[j] & (state[k] >> 1))
                    continue;

                for (size_t l = 0; l <= m; l++)
                    dp[i][j][l + count_one(state[j])] += dp[i - 1][k][l];
            }
        }
    }
}

int main()
{
    std::cin >> n >> m;
    get_state();
    get_dp();

    long long ans = 0;
    for (size_t i = 0; i < state.size(); i++)
        ans += dp[n - 1][i][m];
    std::cout << ans;
    return 0;
}