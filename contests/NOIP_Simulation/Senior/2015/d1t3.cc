#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

const int INF = 0x7fffffff;
const int MAXN = 100;
int num[MAXN];
int ans;

inline void dfs(int times);

namespace straight
{
    // Solve straights
    // times: times in dfs()
    // number: Number of straight (1:single, 2:double, 3:triple)
    inline void straight(int times, int number)
    {
        int length = 0;
        for (int i = 3; i <= 14; i++) // Not containing '2' and Jokers
        {
            if (num[i] <= number - 1)
                length = 0;
            else
            {
                length++;

                int limit;
                if (number == 1) // Single
                    limit = 5;
                else if (number == 2) // Double
                    limit = 3;
                else // Triple
                    limit = 2;

                if (length >= limit)
                {
                    for (int j = i - length + 1; j <= i; j++) // Play
                        num[j] -= number;

                    dfs(times + 1); // Continue

                    for (int j = i - length + 1; j <= i; j++) // Revert
                        num[j] += number;
                }
            }
        }
    }

    // Use void straight()
    // times: times in dfs()
    inline void solve(int times)
    {
        for (int i = 1; i <= 3; i++)
            straight(times, i);
    }
} // namespace straight

namespace take
{
    inline void take(int times, int token_card, int type)
    {
        // addon_type
        // |AAAB|AAABB|AAAABC|AAAABBCC|
        // |1   |2    |3     |4       |

        int limit;
        int token_length;
        int addon1_length;
        int addon2_length = 0;

        if (type == 1)
        {
            limit = 15;
            token_length = 3;
            addon1_length = 1;
        }
        if (type == 2)
        {
            limit = 14;
            token_length = 3;
            addon1_length = 2;
        }
        if (type == 3)
        {
            limit = 15;
            token_length = 4;
            addon1_length = 1;
            addon2_length = 1;
        }
        if (type == 4)
        {
            limit = 14;
            token_length = 4;
            addon1_length = 2;
            addon2_length = 2;
        }

        num[token_card] -= token_length; // Play token

        for (int i = 2; i <= limit; i++)
        {
            if (i == token_card || num[i] <= addon1_length - 1)
                continue;

            num[i] -= addon1_length; // Play addon1

            if (token_length == 3)
                dfs(times + 1);
            else
            {
                for (int j = 2; j <= limit; j++)
                {
                    if (i == j || num[j] <= addon2_length - 1)
                        continue;

                    num[j] -= addon2_length; // Play addon2
                    dfs(times + 1);          // Continue
                    num[j] += addon2_length; // Revert
                }
            }

            num[i] += addon1_length; // Revert
        }

        num[token_card] += token_length; // Revert
    }

    // Use void take()
    // times: times in dfs()
    // Solve cards with cards
    inline void solve(int times)
    {
        for (int i = 2; i <= 14; i++)
        {
            if (num[i] >= 3)
            {
                take(times, i, 1);
                take(times, i, 2);
            }
            if (num[i] == 4)
            {
                take(times, i, 3);
                take(times, i, 4);
            }
        }
    }
} // namespace take

inline int solve_left()
{
    int res = 0;
    for (int i = 2; i <= 15; i++)
        if (num[i] > 0)
            res++;

    return res;
}

inline void dfs(int times) // Number of rounds
{
    if (times > ans)
        return;

    straight::solve(times);
    take::solve(times);
    int left_times = solve_left();

    ans = std::min(ans, times + left_times);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int T, n;
    std::cin >> T >> n;
    while (T--)
    {
        ans = INF;
        std::memset(num, 0, sizeof(num));
        for (int i = 0; i < n; i++)
        {
            // |3|4|5|6|7|8|9|10|J |Q |K |A|2|JK|
            // |3|4|5|6|7|8|9|10|11|12|13|1|2|0 |

            int card; // Card number
            int type; // Card type
            std::cin >> card >> type;

            if (card == 0) // Joker
                num[15]++;
            else if (card == 1) // A
                num[14]++;
            else // Others
                num[card]++;
        }

        dfs(0);
        std::cout << ans << "\n";
    }
    return 0;
}