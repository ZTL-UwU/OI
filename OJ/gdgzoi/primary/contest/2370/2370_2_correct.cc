#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

const int MAX_K = 2e1;
const int MAX_STATE = 2e1 * 2e1 * 2e1 * 2e1;
int flag[MAX_STATE];
bool used[MAX_STATE];
int next[MAX_STATE];
int respawn[MAX_K];
int k;

inline std::vector<int> decode(int state)
{
    std::vector<int> res;
    res.resize(4);

    for (int i = 3; i >= 0; i--)
    {
        res[i] = state % (k + 1);
        state /= (k + 1);
    }
    return res;
}

inline int encode(std::vector<int> board)
{
    int res = 0;
    for (auto i : board)
        res = res * (k + 1) + i;
    return res;
}

inline int damage(int state)
{
    std::vector<int> board;
    board = decode(state);

    bool found = false;
    for (size_t i = 0; i < board.size(); i++)
    {
        if (board[i] > 0)
        {
            board[i]--;

            if (board[i] > 0)
            {
                for (size_t j = 0; j < board.size(); j++)
                {
                    if (board[j] == 0)
                    {
                        board[j] = respawn[board[i]];
                        break;
                    }
                }
            }
            else
                found = true;
        }
    }

    if (not found)
        return -1;
    return encode(board);
}

inline void check(int state)
{
    if (used[state])
        return;
    used[state] = true;

    if (next[state] == -1)
    {
        flag[state] = 2;
        return;
    }

    check(next[state]);
    if (flag[next[state]] == 2)
        flag[state] = 2;
    else
        flag[state] = 1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> k;
    for (int i = 1; i <= k - 1; i++)
        std::cin >> respawn[i];

    next[0] = -1;
    int max_state = std::pow(k + 1, 4);
    for (int i = 1; i <= max_state; i++)
        next[i] = damage(i);

    for (int i = 1; i <= max_state; i++)
        check(i);

    int ans = 0;
    for (int i = 1; i <= max_state; i++)
        if (flag[i] == 1)
            ans++;
    std::cout << ans;
    return 0;
}