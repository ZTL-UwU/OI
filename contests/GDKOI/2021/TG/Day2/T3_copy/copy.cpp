#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>

const int MAX_N = 1e6 + 10;
const int MAX_C = 26;

int right_border[MAX_N];
std::string target_str;
std::vector<int> ps;
int cost[MAX_C];
int dp[MAX_N];

void search(int l, int r)
{
    while (l >= 0 and r < target_str.size() and target_str[l] == target_str[r])
    {
        l--;
        r++;
    }

    l++;
    r--;

    ps.push_back((l + r) / 2);
    right_border[r] = ps.size() - 1;
}

int main()
{
    for (int i = 0; i < MAX_N; i++)
        right_border[i] = -1;

    std::freopen("copy.in", "r", stdin);
    std::freopen("copy.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, c;
    std::cin >> n >> c;

    for (int i = 0; i < 26; i++)
        std::cin >> cost[i];

    std::cin >> target_str;

    for (std::size_t i = 1; i < target_str.size() - 1; i++)
    {
        if (target_str[i - 1] == target_str[i + 1])
            search(i - 1, i + 1);
        if (target_str[i - 1] == target_str[i])
            search(i - 1, i);
        if (target_str[i] == target_str[i + 1])
            search(i, i + 1);
    }

    std::memset(dp, 127, sizeof(dp));
    dp[0] = cost[target_str[0] - 'a'];

    for (int i = 1; i < n; i++)
    {
        dp[i] = std::min(dp[i], dp[i - 1] + cost[target_str[i] - 'a']);

        for (int j = i; j < n; j++)
            if (right_border[j] != -1 and ps[right_border[j]] < i)
                dp[i] = std::min(dp[i], dp[ps[right_border[j]]] + c);
    }

    std::cout << dp[n - 1];
    return 0;
}
